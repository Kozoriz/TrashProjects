#include "servo_adapter/servo_adapter_impl.h"
#include "utils/logger.h"
#include "utils/arduino_mmap_worker_singletone.h"

CREATE_LOGGER("ServoAdapter")

servo_adapter::ServoAdapterImpl::ServoAdapterImpl(
    const servo_adapter::ServoAdapterImpl::Position pos)
    : position_(pos), current_angle_(0) {}

void servo_adapter::ServoAdapterImpl::ChangeAngle(
    const utils::Int angle_delta) {
  LOG_AUTO_TRACE();
  LOG_DEBUG("Angle changed for : " << angle_delta);
  utils::DroneAction act =
      (servo_adapter::ServoAdapterImpl::HORIZONTAL == position_)
          ? utils::DroneAction::HOR_SERVO
          : utils::DroneAction::VER_SERVO;
  current_angle_ += angle_delta;
  utils::MmapWorker::getInstance()->WriteNewStateToMap(act, current_angle_);
}

void servo_adapter::ServoAdapterImpl::SetAngle(const utils::UInt new_angle) {
  LOG_AUTO_TRACE();
  LOG_DEBUG("Angle changed to : " << new_angle);
  utils::DroneAction act =
      (servo_adapter::ServoAdapterImpl::HORIZONTAL == position_)
          ? utils::DroneAction::HOR_SERVO
          : utils::DroneAction::VER_SERVO;
  current_angle_ = new_angle;
  utils::MmapWorker::getInstance()->WriteNewStateToMap(act, current_angle_);
}
