#include "snapshot_processor/snapshot.h"

// TODO move to utils (abs())
#include <cstdlib>

#include "utils/logger.h"

CREATE_LOGGER("SnapshotPorcessor")

namespace snapshot_processor {
    const utils::Byte point_existence_value = 1u;
void Snapshot::AddPoint(const utils::positions::Location3& point) {
    LOG_AUTO_TRACE();
  utils::Byte octal_byte = 0;
  if (point.x_ < 0) {
    octal_byte &= 0x01;
  }
  if (point.y_ < 0) {
    octal_byte &= 0x02;
  }
  if (point.z_ < 0) {
    octal_byte &= 0x04;
  }

  utils::UInt x_pos = std::abs(point.x_);
  utils::UInt y_pos = std::abs(point.y_);
  utils::UInt z_pos = std::abs(point.z_);

  utils::Stringstream ss;
  ss << "[" << point.x_ << ", " << point.y_ << ", " << point.z_ << "]";
  const utils::String stringified_location = ss.str();

  switch (static_cast<Octal>(octal_byte)) {
    case Octal::I: {
      LOG_DEBUG("Location : " << stringified_location << " added to I quadrant");
      I_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    case Octal::II: {
      LOG_DEBUG("Location : " << stringified_location << " added to II quadrant");
      II_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    case Octal::III: {
      LOG_DEBUG("Location : " << stringified_location << " added to II quadrant");
      III_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    case Octal::IV: {
      LOG_DEBUG("Location : " << stringified_location << " added to IV quadrant");
      IV_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    case Octal::V: {
      LOG_DEBUG("Location : " << stringified_location << " added to V quadrant");
      V_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    case Octal::VI: {
      LOG_DEBUG("Location : " << stringified_location << " added to VI quadrant");
      VI_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    case Octal::VII: {
      LOG_DEBUG("Location : " << stringified_location << " added to VII quadrant");
      VII_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    case Octal::VIII: {
      LOG_DEBUG("Location : " << stringified_location << " added to VIII quadrant");
      VIII_quadrant.SetValue(x_pos, y_pos, z_pos, point_existence_value);
      break;
    }
    default: {
      LOG_ERROR("Can`t to identify quadrant for : " << stringified_location);
      break; }
  }
}
}  // namespace snapshot_processor
