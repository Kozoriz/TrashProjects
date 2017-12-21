#include "guide/guide_impl.h"
#include "utils/logger.h"

CREATE_LOGGER("Guide")

namespace guide {
GuideImpl::GuideImpl(const utils::Profile& settings) : settings_(settings) {
  LOG_AUTO_TRACE();
}
GuideImpl::~GuideImpl() {
  LOG_AUTO_TRACE();
}

const utils::positions::Location3& GuideImpl::GetDroneLocation() {
  LOG_AUTO_TRACE();
  return current_dislocation_;
}

PointsArray GuideImpl::GetWayPointsToNearestLocation(
    const PointsArray& possible_analisation_points) {
  LOG_AUTO_TRACE();
  // TODO
  return PointsArray();
}
}
