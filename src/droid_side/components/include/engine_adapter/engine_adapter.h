#pragma once

#include "utils/numbers.h"
#include "utils/threads/synchronization/barrier.h"
#include "utils/threads/thread_runnable.h"

namespace engine_adapter {
class EngineAdapter : public utils::threads::ThreadRunnable {
 public:
  virtual void SpinForward(const utils::UInt milliseconds) = 0;
  virtual void SpinBack(const utils::UInt milliseconds) = 0;
  virtual void SetAdapterSynchronizationBarrier(
      utils::synchronization::Barrier* barrier) = 0;
};
}
