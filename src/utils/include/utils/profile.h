#pragma once

#include "utils/containers/string.h"
#include "utils/numbers.h"
namespace utils {

class Profile {
 public:
  virtual utils::UInt mover_adapters_count() const = 0;
  virtual utils::Float engine_centimeters_per_second() const = 0;
  virtual utils::Float engine_angle_per_second() const = 0;
  virtual utils::UInt rotator_max_horyzontal() const = 0;
  virtual utils::UInt rotator_max_vertical() const = 0;
  virtual utils::UInt rotator_min_horyzontal() const = 0;
  virtual utils::UInt rotator_min_vertical() const = 0;
  virtual utils::UInt rotator_step() const = 0;
  virtual const utils::String& server_address() const = 0;
  virtual utils::UInt server_port() const = 0;
};
}
