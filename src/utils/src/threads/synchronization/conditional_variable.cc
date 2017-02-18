#include "utils/threads/synchronization/conditional_variable.h"

namespace utils {
namespace synchronization {

void ConditionalVariable::Wait(Lock& lock) {
  std_cond_var_.wait(lock.std_unique_lock_);
}

ConditionalVariable::ExitState ConditionalVariable::WaitFor(
    Lock& lock, const utils::UInt milliseconds) {
  if (std::cv_status::no_timeout ==
      std_cond_var_.wait_for(lock.std_unique_lock_,
                             std::chrono::milliseconds(milliseconds))) {
    return ExitState::kNoTimeout;
  } else {
    return ExitState::kTimeout;
  }
}

void ConditionalVariable::NotifyOne() {
  std_cond_var_.notify_one();
}

void ConditionalVariable::Broadcast() {
  std_cond_var_.notify_all();
}
}
}
