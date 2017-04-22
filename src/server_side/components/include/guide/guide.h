#pragma once
#include "utils/structures/position.h"

namespace guide {
class Guide {
 public:
  virtual const utils::positions::Location3& GetDroneLocation() = 0;
};
}
