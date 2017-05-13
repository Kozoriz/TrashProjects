#pragma once
#include "utils/structures/position.h"
#include "utils/containers/vector.h"

namespace guide {
typedef utils::Vector<utils::positions::Location3> PointsArray;
class Guide {
 public:
  virtual const utils::positions::Location3& GetDroneLocation() = 0;
  virtual PointsArray GetWayPointsToNearestLocation(
      const PointsArray& possible_analisation_points) = 0;
};
}
