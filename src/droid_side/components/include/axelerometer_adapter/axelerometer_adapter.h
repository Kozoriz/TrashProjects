#pragma once

#include "utils/structures/position.h"

namespace axelerometer_adapter {

class AxelerometerAdapter {
 public:
  virtual utils::positions::Incline GetData() const = 0;
};
}
