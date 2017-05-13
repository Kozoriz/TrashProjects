#include "snapshot_processor/snapshot.h"

// TODO move to utils (abs())
#include <cstdlib>

#include "utils/logger.h"

CREATE_LOGGER("SnapshotPorcessor")

namespace snapshot_processor {
Snapshot::Snapshot() {
  I_quadrant = utils::make_unique<utils::structures::Matrix3>();
  II_quadrant = utils::make_unique<utils::structures::Matrix3>();
  III_quadrant = utils::make_unique<utils::structures::Matrix3>();
  IV_quadrant = utils::make_unique<utils::structures::Matrix3>();
  V_quadrant = utils::make_unique<utils::structures::Matrix3>();
  VI_quadrant = utils::make_unique<utils::structures::Matrix3>();
  VII_quadrant = utils::make_unique<utils::structures::Matrix3>();
  VIII_quadrant = utils::make_unique<utils::structures::Matrix3>();
}

void Snapshot::AddPoint(const utils::positions::Location3& point) {
  LOG_AUTO_TRACE();
  utils::Byte octal_byte = 0;
  if (point.x_ < 0) {
    octal_byte |= 0x01;
  }
  if (point.y_ < 0) {
    octal_byte |= 0x02;
  }
  if (point.z_ < 0) {
    octal_byte |= 0x04;
  }

  utils::UInt x_pos = std::abs(point.x_);
  utils::UInt y_pos = std::abs(point.y_);
  utils::UInt z_pos = std::abs(point.z_);

  utils::Stringstream ss;
  ss << "[" << point.x_ << ", " << point.y_ << ", " << point.z_ << "]";
  const utils::String stringified_location = ss.str();

  switch (static_cast<Octal>(octal_byte)) {
    case Octal::I: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to I quadrant");
      I_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    case Octal::II: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to II quadrant");
      II_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    case Octal::III: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to II quadrant");
      III_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    case Octal::IV: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to IV quadrant");
      IV_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    case Octal::V: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to V quadrant");
      V_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    case Octal::VI: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to VI quadrant");
      VI_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    case Octal::VII: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to VII quadrant");
      VII_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    case Octal::VIII: {
      LOG_DEBUG("Location : " << stringified_location
                              << " added to VIII quadrant");
      VIII_quadrant->AddPoint(x_pos, y_pos, z_pos);
      break;
    }
    default: {
      LOG_ERROR("Can`t to identify quadrant for : " << stringified_location);
      break;
    }
  }
}

void Snapshot::Clear() {
  I_quadrant->Clear();
  II_quadrant->Clear();
  III_quadrant->Clear();
  IV_quadrant->Clear();
  V_quadrant->Clear();
  VI_quadrant->Clear();
  VII_quadrant->Clear();
  VIII_quadrant->Clear();
}

const utils::structures::Matrix3& Snapshot::GetQuadrant(Octal octal) {
  switch (octal) {
    case Octal::I:
      return *I_quadrant;
    case Octal::II:
      return *II_quadrant;
    case Octal::III:
      return *III_quadrant;
    case Octal::IV:
      return *IV_quadrant;
    case Octal::V:
      return *V_quadrant;
    case Octal::VI:
      return *VI_quadrant;
    case Octal::VII:
      return *VII_quadrant;
    case Octal::VIII:
      return *VIII_quadrant;
    default:
      break;
  }
}

utils::positions::Location3 Snapshot::ShiftToOctal(
    const utils::positions::Location3& point, Octal octal) {
  utils::Int int_octal = static_cast<utils::Int>(octal);
  utils::positions::Location3 temp = point;
  temp.x_ *= (int_octal & 0x01) ? -1 : 1;
  temp.y_ *= (int_octal & 0x02) ? -1 : 1;
  temp.z_ *= (int_octal & 0x04) ? -1 : 1;
  return temp;
}
}  // namespace snapshot_processor
