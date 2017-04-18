#include "snapshot_processor/snapshot_processor_impl.h"
#include "utils/logger.h"

CREATE_LOGGER("SnapshotProcessor")

namespace snapshot_processor {
SnapshotProcessorImpl::SnapshotProcessorImpl(const utils::Profile& settings)
    : settings_(settings) {
  LOG_AUTO_TRACE();
}
SnapshotProcessorImpl::~SnapshotProcessorImpl() {
  LOG_AUTO_TRACE();
}

const Snapshot& SnapshotProcessorImpl::GetGeneratedSnapshot() const {
  LOG_AUTO_TRACE();
  return snapshot_;
}

/*
 * sphere to decart :
 * x=r*sin(a)*cos(b)
 * y=r*sin(a)*sin(b)
 * z=r*cos(a)
 *
 * a - colatitude, angle from Z to line (90 - beta)
 * b - azimut, angle from X to line (alpha)
 */
void SnapshotProcessorImpl::OnMessageReceived(
    const messages::SensorDataMessage& message) {
  LOG_AUTO_TRACE();

  const utils::positions::Incline& angles = message.GetIncline();
  const utils::Float a = static_cast<utils::Float>(90 - angles.beta_);
  const utils::Float b = static_cast<utils::Float>(angles.alpha_);
  const utils::Float radius = static_cast<utils::Float>(message.GetDistance());
  LOG_DEBUG("Received data : R(" << radius << "), Alpha(" << a << "), Beta("
                                 << b << ")");
  utils::positions::Location3 point;
  // TODO wrap sin/cos in utils
  point.x_ = static_cast<utils::Int>(radius * std::sin(a) * std::cos(b));
  point.y_ = static_cast<utils::Int>(radius * std::sin(a) * std::sin(b));
  point.z_ = static_cast<utils::Int>(radius * std::cos(a));

  snapshot_.AddPoint(point);
}

void SnapshotProcessorImpl::ClearSnapshot() {
  LOG_AUTO_TRACE();
  snapshot_ = Snapshot();
}
}
