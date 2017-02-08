#include "utils/synchronization/conditional_variable.h"

namespace utils {
namespace synchronization {

ConditionalVariable::ConditionalVariable()
{

}

ConditionalVariable::~ConditionalVariable()
{

}

void ConditionalVariable::Wait(Lock &lock) {}
void ConditionalVariable::WaitFor(Lock &lock, const utils::UInt milliseconds) {}
void ConditionalVariable::NotifyOne() {}
void ConditionalVariable::Broadcast() {}

}
}
