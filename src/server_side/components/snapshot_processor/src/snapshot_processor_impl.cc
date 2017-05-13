#include "snapshot_processor/snapshot_processor_impl.h"

#include "utils/file_system.h"
#include "utils/date_time.h"

#include "utils/logger.h"

CREATE_LOGGER("SnapshotProcessor")

namespace snapshot_processor {
SnapshotProcessorImpl::SnapshotProcessorImpl(const utils::Profile& settings)
    : settings_(settings) {
  LOG_AUTO_TRACE();
  snapshot_ = utils::make_shared<Snapshot>();
}
SnapshotProcessorImpl::~SnapshotProcessorImpl() {
  LOG_AUTO_TRACE();
}

SnapshotSPtr SnapshotProcessorImpl::GetGeneratedSnapshot() const {
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
  LOG_DEBUG("Received data : R(" << radius << "), Colatitude(" << a
                                 << "), Azimut(" << b << ")");
  // need converting to radians (because sin and cos works with it)
  const utils::Float a_rad = a * M_PI / 180;
  const utils::Float b_rad = b * M_PI / 180;

  utils::positions::Location3 point;
  // TODO wrap sin/cos in utils
  point.x_ =
      static_cast<utils::Int>(radius * std::sin(a_rad) * std::cos(b_rad));
  point.y_ =
      static_cast<utils::Int>(radius * std::sin(a_rad) * std::sin(b_rad));
  point.z_ = static_cast<utils::Int>(radius * std::cos(a_rad));

  snapshot_->AddPoint(point);
}

void SnapshotProcessorImpl::ClearSnapshot() {
  LOG_AUTO_TRACE();
  snapshot_->Clear();
  LOG_DEBUG("Snapshot cleared.");
}

void SnapshotProcessorImpl::SaveSnapshotFile() const {
  using namespace utils::file_system;
  LOG_AUTO_TRACE();

  const utils::String name =
      utils::date_time::GetDateTimeString("Snapshot_%Y_%m_%d_%I_%M_%S");
  File file(name);
  file.Open(File::OpenMode::Write);

  for (int i = 0; i < 8; ++i) {
    const utils::structures::Matrix3& quadrant =
        snapshot_->GetQuadrant(static_cast<Octal>(i));
    for (auto point : quadrant) {
      utils::positions::Location3 shifted_point =
          snapshot_->ShiftToOctal(point, static_cast<Octal>(i));
      file.WriteLine(shifted_point.ToString());
    }
  }
  file.Close();
}
}  // namespace snapshot_processor
