#pragma once

#include "engine_adapter/engine_adapter.h"
#include "mover/mover.h"
#include "utils/profile.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/threads/synchronization/barrier.h"
#include "utils/threads/thread.h"

namespace mover {
class TankTrackMover : public Mover {
 public:
  TankTrackMover(engine_adapter::EngineAdapter& left,
                 engine_adapter::EngineAdapter& right,
                 const utils::Profile& settings);
  ~TankTrackMover();
  void OnMoveMessageReceived(const MoveMessage& message) override;
  void Run() override;
  void Join() override;

 private:
  void Move(const utils::Int centimeters) const;
  void Rotate(const utils::Int angle) const;

 private:
  engine_adapter::EngineAdapter& left_track_adapter_;
  engine_adapter::EngineAdapter& right_track_adapter_;
  const utils::Profile& settings_;
  utils::threads::Thread left_track_thread_;
  utils::threads::Thread right_track_thread_;
  utils::synchronization::AtomicBool finalizyng_;
  utils::synchronization::Barrier adapters_waiting_barrier_;
};
}
