#include "servo_adapter/servo_adapter_impl.h"
#include "utils/logger.h"

CREATE_LOGGER("ServoAdapter")

void servo_adapter::ServoAdapterImpl::ChangeAngle(
    const utils::Int angle_delta) {
  LOG_AUTO_TRACE();
  LOG_DEBUG("Angle changed for : " << angle_delta);
}

void servo_adapter::ServoAdapterImpl::SetAngle(const utils::UInt new_angle) {
  LOG_AUTO_TRACE();
  LOG_DEBUG("Angle changed to : " << new_angle);
}
