#pragma once

#include "utils/numbers.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/threads/synchronization/conditional_variable.h"
#include "utils/threads/synchronization/lock.h"

namespace utils {
namespace synchronization {
class Barrier {
 public:
  Barrier(const utils::UInt count);
  void set_count(const utils::UInt count);
  void Wait();

 private:
  utils::synchronization::Atomic<utils::UInt> count_;
  utils::synchronization::Lock lock_;
  utils::synchronization::ConditionalVariable cond_var_;
};
}
}
