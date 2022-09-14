/***
 * @Author       : shiyucun
 * @Date         : 2022-05-03 23:01:37
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-05-03 23:03:25
 * @Description  : 读写锁单元测试
 */

#include "common/base/atomic_rw_lock.hpp"

#include "gtest/gtest.h"

namespace JustFollow {
namespace Common {
namespace Base {

TEST(AtomicRWLockUt, write_then_read) {
  std::atomic<bool> data_locked{false};
  std::atomic<int> thread_num{0};

  int data_w = 0;
  int data_r = 0;

  bool running = true;

  AtomicRWLock lock;

  auto f1 = [&] {
    thread_num++;

    WriteLockGuard<AtomicRWLock> wlg(lock);
    data_locked.store(std::memory_order_release);

    std::this_thread::yield();
    std::this_thread::yield();
    std::this_thread::yield();

    data_w = 0x123456;

    while (running) {
      std::this_thread::yield();
    }
  };

  auto f2 = [&]() {
    thread_num++;

    while (!data_locked.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }

    ReadLockGuard<AtomicRWLock> rlg(lock);
    data_r = data_w;

    while (running) {
      std::this_thread::yield();
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  while (thread_num != 2) {
    std::this_thread::yield();
  }

  running = false;
  t1.join();
  t2.join();

  EXPECT_EQ(data_w, data_r);
}

TEST(AtomicRWLockUt, read_then_write) {
  std::atomic<bool> data_locked{false};
  std::atomic<int> thread_num{0};

  int data_w = 0x123456;
  int data_r = 0;

  bool running = true;

  AtomicRWLock lock;

  auto f1 = [&] {
    thread_num++;

    ReadLockGuard<AtomicRWLock> rlg(lock);
    data_locked.store(std::memory_order_release);

    std::this_thread::yield();
    std::this_thread::yield();
    std::this_thread::yield();

    data_r = data_w;

    while (running) {
      std::this_thread::yield();
    }
  };

  auto f2 = [&]() {
    thread_num++;

    while (!data_locked.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }

    WriteLockGuard<AtomicRWLock> wlg(lock);
    data_w = 0;

    while (running) {
      std::this_thread::yield();
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  while (thread_num != 2) {
    std::this_thread::yield();
  }

  running = false;
  t1.join();
  t2.join();

  EXPECT_EQ(data_w, 0);
  EXPECT_EQ(data_r, 0x123456);
}

TEST(AtomicRWLockUt, write_then_write) {
  std::atomic<bool> data_locked{false};
  std::atomic<int> thread_num{0};

  int data = 0;

  bool running = true;

  AtomicRWLock lock;

  auto f1 = [&]() {
    thread_num++;

    WriteLockGuard<AtomicRWLock> wlg(lock);
    data_locked.store(std::memory_order_release);

    std::this_thread::yield();
    std::this_thread::yield();
    std::this_thread::yield();

    data = 0x123456;

    while (running) {
      std::this_thread::yield();
    }
  };

  auto f2 = [&]() {
    thread_num++;

    while (!data_locked.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }

    WriteLockGuard<AtomicRWLock> wlg(lock);
    data = 0x654321;

    while (running) {
      std::this_thread::yield();
    }
  };

  std::thread t1(f1);
  std::thread t2(f2);

  while (thread_num != 2) {
    std::this_thread::yield();
  }

  running = false;
  t1.join();
  t2.join();

  EXPECT_EQ(data, 0x654321);
}

}  // namespace Base
}  // namespace Common
}  // namespace JustFollow