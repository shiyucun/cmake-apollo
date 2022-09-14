/***
 * @Author       : shiyucun
 * @Date         : 2022-04-20 14:56:32
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-04-20 14:56:33
 * @Description  : 无锁哈希表
 */

#pragma once

#include "macros.hpp"

#include <cstdint>

#include <atomic>
#include <type_traits>
#include <utility>

namespace JustFollow {
namespace Common {
namespace Base {

/***
 * @description: 无锁固定长度的哈希表
 * @param {KEY} 哈希表key值的类型
 * @param {VALUE} 哈希表value值的类型
 * @param {TABLE_SIZE} 哈希表的长度，默认值为128
 * @param {enable_if} 哈希表key值需要是int类型，并且表的大小需要是2^n
 */
template <typename KEY, typename VALUE, std::size_t TABLE_SIZE = 128,
          typename std::enable_if<
              std::is_integral<KEY>::value && (TABLE_SIZE & (TABLE_SIZE - 1)) == 0, int>::type = 0>
class AtomicHashMap {
 public:
  AtomicHashMap() : capacity_(TABLE_SIZE), index_mask_(capacity_ - 1) {}

  bool Has(KEY key) {
    uint64_t index = key & index_mask_;
    return table_[index].Has(key);
  }

  bool Get(KEY key, VALUE **value) {
    uint64_t index = key & index_mask_;
    return table_[index].Get(key, value);
  }

  bool Get(KEY key, VALUE *value) {
    uint64_t index = key & index_mask_;
    VALUE *v = nullptr;
    bool res = table_[index].Get(key, &v);
    if (res) {
      *value = *v;
    }
    return res;
  }

  void Set(KEY key) {
    uint64_t index = key & index_mask_;
    table_[index].Insert(key);
  }

  void Set(KEY key, const VALUE &value) {
    uint64_t index = key & index_mask_;
    table_[index].Insert(key, value);
  }

  void Set(KEY key, VALUE &&value) {
    uint64_t index = key & index_mask_;
    table_[index].Insert(key, std::forward<VALUE>(value));
  }

  DISALLOW_COPY_AND_ASSIGN(AtomicHashMap)

 private:
  struct Node {
    Node() {}

    explicit Node(KEY key) : key(key) { value_ptr.store(new VALUE(), std::memory_order_release); }

    Node(KEY key, const VALUE &value) : key(key) {
      value_ptr.store(new VALUE(value), std::memory_order_release);
    }

    Node(KEY key, VALUE &&value) : key(key) {
      value_ptr.store(new VALUE(std::forward<VALUE>(value)), std::memory_order_release);
    }

    ~Node() { delete value_ptr.load(std::memory_order_acquire); }

    KEY key{0};
    std::atomic<VALUE *> value_ptr{nullptr};
    std::atomic<Node *> next{nullptr};
  };

  class Bucket {
   public:
    Bucket() : head_(new Node()) {}
    ~Bucket() {
      Node *iter = head_;
      while (iter) {
        auto tmp = iter->next.load(std::memory_order_acquire);
        delete iter;
        iter = tmp;
      }
    }

    bool Has(KEY key) {
      Node *m_target = head_->next.load(std::memory_order_acquire);
      while (Node *target = m_target) {
        if (target->key < key) {
          m_target = target->next.load(std::memory_order_acquire);
          continue;
        } else {
          return target->key == key;
        }
      }
      return false;
    }

    bool Find(KEY key, Node **prev_ptr, Node **target_ptr) {
      Node *prev = head_;
      Node *m_target = head_->next.load(std::memory_order_acquire);
      while (Node *target = m_target) {
        if (target->key == key) {
          *prev_ptr = prev;
          *target_ptr = target;
          return true;
        } else if (target->key > key) {
          *prev_ptr = prev;
          *target_ptr = target;
          return false;
        } else {
          prev = target;
          m_target = target->next.load(std::memory_order_acquire);
        }
      }
      *prev_ptr = prev;
      *target_ptr = nullptr;
      return false;
    }

    void Insert(KEY key, const VALUE &value) {
      Node *prev = nullptr;
      Node *target = nullptr;
      Node *new_node = nullptr;
      VALUE *new_value = nullptr;

      while (true) {  // 其它线程更新了哈希表时compare_exchange_strong有可能会失败，需重新进行
        if (Find(key, &prev, &target)) {
          if (!new_value) {
            new_value = new VALUE(value);
          }
          auto old_val_ptr = target->value_ptr.load(std::memory_order_acquire);
          if (target->value_ptr.compare_exchange_strong(
                  old_val_ptr, new_value, std::memory_order_acq_rel, std::memory_order_relaxed)) {
            delete old_val_ptr;
            if (new_node) {
              delete new_node;
              new_node = nullptr;
            }
            return;
          }
          continue;
        } else {
          if (!new_node) {
            new_node = new Node(key, value);
          }
          new_node->next.store(target, std::memory_order_release);
          if (prev->next.compare_exchange_strong(target, new_node, std::memory_order_acq_rel,
                                                 std::memory_order_relaxed)) {
            if (new_value) {
              delete new_value;
              new_value = nullptr;
            }
            return;
          }
        }
      }
    }

    void Insert(KEY key, VALUE &&value) {
      Node *prev = nullptr;
      Node *target = nullptr;
      Node *new_node = nullptr;
      VALUE *new_value = nullptr;

      while (true) {  // 其它线程更新了哈希表时compare_exchange_strong有可能会失败，需重新进行
        if (Find(key, &prev, &target)) {
          if (!new_value) {
            new_value = new VALUE(std::forward<VALUE>(value));
          }
          auto old_val_ptr = target->value_ptr.load(std::memory_order_acquire);
          if (target->value_ptr.compare_exchange_strong(
                  old_val_ptr, new_value, std::memory_order_acq_rel, std::memory_order_relaxed)) {
            delete old_val_ptr;
            if (new_node) {
              delete new_node;
              new_node = nullptr;
            }
            return;
          }
          continue;
        } else {
          if (!new_node) {
            new_node = new Node(key, value);
          }
          new_node->next.store(target, std::memory_order_release);
          if (prev->next.compare_exchange_strong(target, new_node, std::memory_order_acq_rel,
                                                 std::memory_order_relaxed)) {
            if (new_value) {
              delete new_value;
              new_value = nullptr;
            }
            return;
          }
        }
      }
    }

    void Insert(KEY key) {
      Node *prev = nullptr;
      Node *target = nullptr;
      Node *new_node = nullptr;
      VALUE *new_value = nullptr;

      while (true) {  // 其它线程更新了哈希表时compare_exchange_strong有可能会失败，需重新进行
        if (Find(key, &prev, &target)) {
          if (!new_value) {
            new_value = new VALUE();
          }
          auto old_val_ptr = target->value_ptr.load(std::memory_order_acquire);
          if (target->value_ptr.compare_exchange_strong(
                  old_val_ptr, new_value, std::memory_order_acq_rel, std::memory_order_relaxed)) {
            delete old_val_ptr;
            if (new_node) {
              delete new_node;
              new_node = nullptr;
            }
            return;
          }
          continue;
        } else {
          if (!new_node) {
            new_node = new Node(key);
          }
          new_node->next.store(target, std::memory_order_release);
          if (prev->next.compare_exchange_strong(target, new_node, std::memory_order_acq_rel,
                                                 std::memory_order_relaxed)) {
            if (new_value) {
              delete new_value;
              new_value = nullptr;
            }
            return;
          }
        }
      }
    }

    bool Get(KEY key, VALUE **value) {
      Node *prev = nullptr;
      Node *target = nullptr;
      if (Find(key, &prev, &target)) {
        *value = target->value_ptr.load(std::memory_order_acquire);
        return true;
      }
      return false;
    }

    Node *head_;
  };

 private:
  Bucket table_[TABLE_SIZE];
  uint64_t capacity_;
  uint64_t index_mask_;
};

}  // namespace Base
}  // namespace Common
}  // namespace JustFollow
