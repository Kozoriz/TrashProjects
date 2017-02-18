#pragma once

#include "utils/containers/string.h"
#include "utils/profile.h"

namespace utils {
class ProfileImpl : public Profile {
 public:
  ProfileImpl(const utils::String& file_name);
  utils::UInt mover_adapters_count() const override;
  utils::Float engine_centimeters_per_second() const override;
  utils::Float engine_angle_per_second() const override;
  utils::UInt rotator_max_horyzontal() const override;
  utils::UInt rotator_max_vertical() const override;
  utils::UInt rotator_min_horyzontal() const override;
  utils::UInt rotator_min_vertical() const override;
  const utils::String& server_address() const override;
  utils::UInt server_port() const override;
};
}
