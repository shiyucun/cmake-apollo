/***
 * @Author       : shiyucun
 * @Date         : 2022-05-03 17:35:56
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-05-03 17:44:53
 * @Description  : 可重入读写锁
 */

#pragma once

#include "macros.hpp"
#include "rw_lock_guard.hpp"

#include <cstdint>

#include <thread>

namespace JustFollow {
namespace Common {
namespace Base {

static const std::thread::id NULL_THREAD_ID = std::thread::id();

class ReentrantRWLock {
  friend class ReadLockGuard<ReentrantRWLock>;
  friend class WriteLockGuard<ReentrantRWLock>;

 public:
  ReentrantRWLock() = default;

  explicit ReentrantRWLock(bool write_first) : write_first_(write_first) {}

  DISALLOW_COPY_AND_ASSIGN(ReentrantRWLock)

 private:
  void ReadLock() {
    if (write_thread_id_ == std::this_thread::get_id()) {
      return;
    }

    uint32_t retry_times = 0;
    int32_t lock_num = lock_num_.load(std::memory_order_acquire);

    if (write_first_) {
      do {
        while (lock_num < RW_LOCK_FREE || write_lock_wait_num_.load(std::memory_order_acquire)) {
          if (++retry_times == MAX_RETRY_TIMES) {
            std::this_thread::yield();
            retry_times = 0;
          }
          lock_num = lock_num_.load(std::memory_order_acquire);
        }
      } while (!lock_num_.compare_exchange_weak(lock_num, lock_num + 1, std::memory_order_acq_rel,
                                                std::memory_order_relaxed));
    } else {
      do {
        while (lock_num < RW_LOCK_FREE) {
          if (++retry_times == MAX_RETRY_TIMES) {
            std::this_thread::yield();
            retry_times = 0;
          }
          lock_num = lock_num_.load(std::memory_order_acquire);
        }
      } while (!lock_num_.compare_exchange_weak(lock_num, lock_num + 1, std::memory_order_acq_rel,
                                                std::memory_order_relaxed));
    }
  }

  void ReadUnLock() {
    if (write_thread_id_ == std::this_thread::get_id()) {
      return;
    }
    lock_num_.fetch_sub(1);
  }

  void WriteLock() {
    auto this_thread_id = std::this_thread::get_id();

    if (write_thread_id_ == this_thread_id) {
      lock_num_.fetch_sub(1);
      return;
    }

    int32_t rw_lock_free = RW_LOCK_FREE;
    uint32_t retry_times = 0;

    write_lock_wait_num_.fetch_add(1);

    while (!lock_num_.compare_exchange_weak(rw_lock_free, WRITE_EXCLUSIVE,
                                            std::memory_order_acq_rel, std::memory_order_relaxed)) {
      rw_lock_free = RW_LOCK_FREE;
      if (++retry_times == MAX_RETRY_TIMES) {
        std::this_thread::yield();
        retry_times = 0;
      }
    }

    write_thread_id_ = this_thread_id;
    write_lock_wait_num_.fetch_sub(1);
  }

  void WriteUnLock() {
    if (lock_num_.fetch_add(1) == WRITE_EXCLUSIVE) {
      write_thread_id_ = NULL_THREAD_ID;
    }
  }

 public:
  static const int32_t RW_LOCK_FREE{0};
  static const int32_t WRITE_EXCLUSIVE{-1};
  static const uint32_t MAX_RETRY_TIMES{5};

  static const std::thread::id null_thread_;

 private:
  std::thread::id write_thread_id_{NULL_THREAD_ID};
  std::atomic<uint32_t> write_lock_wait_num_{0};
  std::atomic<int32_t> lock_num_{0};
  bool write_first_{true};
};

}  // namespace Base
}  // namespace Common
}  // namespace JustFollow