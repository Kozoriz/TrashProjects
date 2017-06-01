#pragma once

#include "engine_adapter/engine_adapter.h"
#include "utils/containers/queue.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/threads/synchronization/conditional_variable.h"

namespace engine_adapter {

class EngineAdapterImpl : public EngineAdapter {
 public:
  enum class Direction { STOP, FORWARD, BACK };
  enum class Position { LEFT, RIGHT };

  EngineAdapterImpl(const Position pos);
  virtual ~EngineAdapterImpl();

  void SpinForward(const utils::UInt milliseconds) override;
  void SpinBack(const utils::UInt milliseconds) override;
  void SetAdapterSynchronizationBarrier(
      utils::synchronization::Barrier* barrier);
  void Run() override;
  void Join() override;

 protected:
  void SpinForwardLowLevel(const utils::UInt milliseconds) const;
  void SpinBackLowLevel(const utils::UInt milliseconds) const;
  void OnSpinDone();

 private:
  utils::synchronization::AtomicBool finalyzing_;
  utils::synchronization::Atomic<Direction> current_state_;
  utils::synchronization::Atomic<utils::UInt> move_value_;
  utils::synchronization::Barrier* synchronization_barrier_;

  const Position engine_position_;
};
}
