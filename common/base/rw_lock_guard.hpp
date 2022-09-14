/***
 * @Author       : shiyucun
 * @Date         : 2022-05-03 15:39:32
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-05-03 15:41:19
 * @Description  : LockGuard对象释放时锁自动释放，用于 AtomicRWLock 和 ReentrantRWLock
 */

#pragma once

#include "macros.hpp"

#include <cstdint>

#include <atomic>

namespace JustFollow {
namespace Common {
namespace Base {

template <typename RW_LOCK>
class ReadLockGuard {
 public:
  explicit ReadLockGuard(RW_LOCK& lock) : lock_(lock) { lock_.ReadLock(); }

  ~ReadLockGuard() { lock_.ReadUnLock(); }

  DISALLOW_COPY_AND_ASSIGN(ReadLockGuard)

 private:
  RW_LOCK& lock_;
};

template <typename RW_LOCK>
class WriteLockGuard {
 public:
  explicit WriteLockGuard(RW_LOCK& lock) : lock_(lock) { lock_.WriteLock(); }

  ~WriteLockGuard() { lock_.WriteUnLock(); }

  DISALLOW_COPY_AND_ASSIGN(WriteLockGuard)

 private:
  RW_LOCK& lock_;
};

}  // namespace Base
}  // namespace Common
}  // namespace JustFollow