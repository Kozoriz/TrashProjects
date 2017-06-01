#pragma once

#include "utils/numbers.h"

namespace sensor_adapter {
class SensorAdapter {
 public:
  virtual utils::Int GetSensorData() const = 0;
};
}
