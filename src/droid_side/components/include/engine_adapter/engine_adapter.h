#pragma once

#include "utils/numbers.h"
#include "utils/threads/synchronization/barrier.h"
#include "utils/threads/thread_runnable.h"

namespace engine_adapter {
/**
 * TODO need to realyze thread for adapters
 * spin methods can just set values but executing trigger via
 * cond_var.notifyall...
 */
class EngineAdapter : public utils::threads::ThreadRunnable {
 public:
  virtual void SpinForward(const utils::UInt milliseconds) = 0;
  virtual void SpinBack(const utils::UInt milliseconds) = 0;
  virtual void SetAdapterSynchronizationBarrier(
      utils::synchronization::Barrier* barrier) = 0;
};
}
