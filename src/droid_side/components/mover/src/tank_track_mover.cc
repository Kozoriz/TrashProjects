#include "mover/tank_track_mover.h"
#include "utils/logger.h"
#include "utils/threads/synchronization/auto_lock.h"

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
  left_track_adapter_.SetAdapterSynchronizationBarrier(
      &adapters_waiting_barrier_);
  right_track_adapter_.SetAdapterSynchronizationBarrier(
      &adapters_waiting_barrier_);
}

mover::TankTrackMover::~TankTrackMover() {
  Join();
}

void mover::TankTrackMover::OnMoveMessageReceived(const MoveMessage& message) {
  utils::synchronization::AutoLock auto_lock(move_queue_lock_);
  move_queue_.push(message);
}

void mover::TankTrackMover::Run() {
  left_track_thread_.StartThread();
  right_track_thread_.StartThread();
  while (!finalizyng_) {
    MoveMessage current_action;
    {
      // TODO investigate problem with deadlock found by UT(repeat > 50)
      utils::synchronization::AutoLock auto_lock_(move_queue_lock_);
      if (!move_queue_.empty()) {
        current_action = move_queue_.front();
        move_queue_.pop();
      } else {
        continue;
      }
    }
    adapters_waiting_barrier_.set_count(settings_.mover_adapters_count() + 1);
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
  finalizyng_ = true;
  left_track_thread_.JoinThread();
  right_track_thread_.JoinThread();
}

void mover::TankTrackMover::Move(const utils::Int centimeters) const {
  /**
   * @brief centimeters_per_second - TODO get data from profile
   */
  utils::Float centimeters_per_second = 3.f;
  utils::Int milliseconds = centimeters / centimeters_per_second;
  if (milliseconds < 0) {
    left_track_adapter_.SpinBack(-milliseconds);
    right_track_adapter_.SpinBack(-milliseconds);
  } else {
    left_track_adapter_.SpinForward(milliseconds);
    right_track_adapter_.SpinForward(milliseconds);
  }
}

void mover::TankTrackMover::Rotate(const utils::Int angle) const {
  /**
   * @brief angle_per_second - TODO get data from profile
   */
  utils::Float angle_per_second = 3.f;
  utils::Int milliseconds = angle / angle_per_second;

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
