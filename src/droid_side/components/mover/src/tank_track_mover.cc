#include "mover/tank_track_mover.h"
#include "utils/logger.h"
#include "utils/synchronization/auto_lock.h"

mover::TankTrackMover::TankTrackMover(
    const engine_adapter::EngineAdapter& left,
    const engine_adapter::EngineAdapter& right)
    : left_track_adapter_(left)
    , right_track_adapter_(right)
    , finalizyng_(false) {}

mover::TankTrackMover::~TankTrackMover() {
  finalizyng_ = true;
}

void mover::TankTrackMover::OnMoveMessageReceived(const MoveMessage* message) {
  utils::synchronization::AutoLock auto_lock(move_queue_lock_);
  if (NULL != message) {
    move_queue_.push(*message);
  }
}

void mover::TankTrackMover::Run() {
  while (!finalizyng_) {
    MoveMessage current_action;
    current_action.move_type_ = MoveType::INVALID_ENUM;
    {
      utils::synchronization::AutoLock auto_lock_(move_queue_lock_);
      if (!move_queue_.empty()) {
        current_action = move_queue_.front();
        move_queue_.pop();
      }
    }
    switch (current_action.move_type_) {
      case MoveType::MOVE_FORWARD: {
        Move(current_action.value_);
        break;
      }
      case MoveType::ROTATE: {
        Rotate(current_action.value_);
        break;
      }
      default:
        // LOG ERROR
        break;
    }
  }
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
    return;
  }
  left_track_adapter_.SpinForward(milliseconds);
  right_track_adapter_.SpinForward(milliseconds);
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
    return;
  }
  // Rotate right
  left_track_adapter_.SpinForward(milliseconds);
  right_track_adapter_.SpinBack(milliseconds);
}
