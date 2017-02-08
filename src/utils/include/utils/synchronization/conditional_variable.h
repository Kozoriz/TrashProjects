#pragma once

#include "utils/synchronization/lock.h"
#include "utils/numbers.h"

namespace utils {
namespace synchronization {
class ConditionalVariable {
 public:
    ConditionalVariable();
    ~ConditionalVariable();

    void Wait(Lock& lock);
    void WaitFor(Lock& lock, const utils::UInt milliseconds);
    void NotifyOne();
    void Broadcast();
private:
};
}
}
