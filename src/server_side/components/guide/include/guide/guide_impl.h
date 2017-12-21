#pragma once
#include "guide/guide.h"
#include "utils/profile.h"

namespace guide {
class GuideImpl : public Guide {
 public:
  GuideImpl(const utils::Profile& settings);
  ~GuideImpl();

  const utils::positions::Location3& GetDroneLocation() override;
  PointsArray GetWayPointsToNearestLocation(
      const PointsArray& possible_analisation_points) override;

 private:
  const utils::Profile& settings_;
  utils::positions::Location3 current_dislocation_;
};
}
