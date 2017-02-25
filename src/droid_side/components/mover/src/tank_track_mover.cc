#include "mover/tank_track_mover.h"
#include "utils/logger.h"
#include "utils/threads/synchronization/auto_lock.h"

CREATE_LOGGER("Mover")

mover::TankTrackMover::TankTrackMover(engine_adapter::EngineAdapter& left,
                                      engine_adapter::EngineAdapter& right,
                                      const utils::Profile& settings)
    : left_track_adapter_(left)
    , right_track_adapter_(right)
    , settings_(settings)
    , left_track_thread_(left_track_adapter_)
    , right_track_thread_(right_track_adapter_)
    , finalizyng_(false)
    , adapters_waiting_barrier_(settings_.mover_adapters_count() + 1) {
  LOG_AUTO_TRACE();
  left_track_adapter_.SetAdapterSynchronizationBarrier(
      &adapters_waiting_barrier_);
  right_track_adapter_.SetAdapterSynchronizationBarrier(
      &adapters_waiting_barrier_);
}

mover::TankTrackMover::~TankTrackMover() {
  LOG_AUTO_TRACE();
  Join();
}

void mover::TankTrackMover::OnMoveMessageReceived(const MoveMessage& message) {
  LOG_AUTO_TRACE();
  utils::synchronization::AutoLock auto_lock(move_queue_lock_);
  move_queue_.PushMessage(message);
}

void mover::TankTrackMover::Run() {
  LOG_AUTO_TRACE();
  left_track_thread_.StartThread();
  right_track_thread_.StartThread();
  while (!finalizyng_) {
    move_queue_.WaitNewMessages();
    adapters_waiting_barrier_.set_count(settings_.mover_adapters_count() + 1);
    MoveMessage current_action;
    {
      // TODO investigate problem with deadlock found by UT(repeat > 50)
      utils::synchronization::AutoLock auto_lock_(move_queue_lock_);
        current_action = move_queue_.GetMessage();
    }
    switch (current_action.move_type()) {
      case MoveType::MOVE_FORWARD: {
        Move(current_action.value());
        adapters_waiting_barrier_.Wait();
        break;
      }
      case MoveType::ROTATE: {
        Rotate(current_action.value());
        adapters_waiting_barrier_.Wait();
        break;
      }
      default:
        break;
    }
  }
}

void mover::TankTrackMover::Join() {
  LOG_AUTO_TRACE();
  finalizyng_ = true;
  left_track_thread_.JoinThread();
  right_track_thread_.JoinThread();
  move_queue_.Finalyze();
}

void mover::TankTrackMover::Move(const utils::Int centimeters) const {
  LOG_AUTO_TRACE();
  utils::Int milliseconds =
      centimeters / settings_.engine_centimeters_per_second();
  if (milliseconds < 0) {
    left_track_adapter_.SpinBack(-milliseconds);
    right_track_adapter_.SpinBack(-milliseconds);
  } else {
    left_track_adapter_.SpinForward(milliseconds);
    right_track_adapter_.SpinForward(milliseconds);
  }
}

void mover::TankTrackMover::Rotate(const utils::Int angle) const {
  LOG_AUTO_TRACE();
  utils::Int milliseconds = angle / settings_.engine_angle_per_second();
  if (milliseconds < 0) {
    // Rotate left
    left_track_adapter_.SpinBack(-milliseconds);
    right_track_adapter_.SpinForward(-milliseconds);
  } else {
    // Rotate right
    left_track_adapter_.SpinForward(milliseconds);
    right_track_adapter_.SpinBack(milliseconds);
  }
}
