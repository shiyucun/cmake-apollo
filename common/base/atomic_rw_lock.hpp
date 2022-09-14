/***
 * @Author       : shiyucun
 * @Date         : 2022-05-03 15:52:22
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-05-03 15:58:33
 * @Description  : 读写锁
 */

#pragma once

#include "macros.hpp"
#include "rw_lock_guard.hpp"

#include <cstdint>

#include <atomic>
#include <thread>

namespace JustFollow {
namespace Common {
namespace Base {

class AtomicRWLock {
  friend class ReadLockGuard<AtomicRWLock>;
  friend class WriteLockGuard<AtomicRWLock>;

 public:
  AtomicRWLock() = default;

  explicit AtomicRWLock(bool write_first) : write_first_(write_first) {}

  DISALLOW_COPY_AND_ASSIGN(AtomicRWLock)

 private:
  void ReadLock() {
    uint32_t retry_times = 0;
    int32_t lock_num = lock_num_.load();

    if (write_first_) {
      do {
        while (lock_num < RW_LOCK_FREE || write_lock_wait_num_.load() > 0) {
          if (++retry_times == MAX_RETRY_TIMES) {
            std::this_thread::yield();
            retry_times = 0;
          }
          lock_num = lock_num_.load();
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
          lock_num = lock_num_.load();
        }
      } while (!lock_num_.compare_exchange_weak(lock_num, lock_num_ + 1, std::memory_order_acq_rel,
                                                std::memory_order_relaxed));
    }
  }

  void ReadUnLock() { lock_num_.fetch_sub(1); }

  void WriteLock() {
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

    write_lock_wait_num_.fetch_sub(1);
  }

  void WriteUnLock() { lock_num_.fetch_add(1); }

 public:
  static const int32_t RW_LOCK_FREE{0};
  static const int32_t WRITE_EXCLUSIVE{-1};
  static const uint32_t MAX_RETRY_TIMES{5};

 private:
  std::atomic<uint32_t> write_lock_wait_num_{0};
  std::atomic<int32_t> lock_num_{0};
  bool write_first_{true};
};

}  // namespace Base
}  // namespace Common
}  // namespace JustFollow