#pragma once

#include "engine_adapter/engine_adapter.h"
#include "mover/mover.h"
#include "utils/synchronization/atomic.h"

namespace mover {
class TankTrackMover : public Mover {
 public:
  TankTrackMover(const engine_adapter::EngineAdapter& left,
                 const engine_adapter::EngineAdapter& right);
  ~TankTrackMover();
  void OnMoveMessageReceived(const MoveMessage* message) override;
  void Run() override;

 private:
  void Move(const utils::Int centimeters) const;
  void Rotate(const utils::Int angle) const;

 private:
  const engine_adapter::EngineAdapter& left_track_adapter_;
  const engine_adapter::EngineAdapter& right_track_adapter_;
  utils::synchronization::AtomicBool finalizyng_;
};
}
