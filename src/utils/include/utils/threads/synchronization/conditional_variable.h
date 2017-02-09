#pragma once

#include <condition_variable>
#include "utils/numbers.h"
#include "utils/threads/synchronization/lock.h"

namespace utils {
namespace synchronization {
class ConditionalVariable {
 public:
    void Wait(Lock& lock);
    void WaitFor(Lock& lock, const utils::UInt milliseconds);
    void NotifyOne();
    void Broadcast();
private:
    std::condition_variable std_cond_var_;
};
}
}
