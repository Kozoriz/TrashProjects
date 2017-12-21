#pragma once

#include "utils/numbers.h"

namespace servo_adapter {
class ServoAdapter {
 public:
  virtual void ChangeAngle(const utils::Int angle_delta) = 0;
  virtual void SetAngle(const utils::UInt new_angle) = 0;
};
}
