#include "utils/profile_impl.h"

utils::ProfileImpl::ProfileImpl(const utils::String& file_name) {
  // TODO : read data from file
}

utils::UInt utils::ProfileImpl::mover_adapters_count() const {
  return 3;
}

utils::Float utils::ProfileImpl::engine_centimeters_per_second() const {
  return 2.f;
}

utils::Float utils::ProfileImpl::engine_angle_per_second() const {
  return 1.f;
}

utils::UInt utils::ProfileImpl::rotator_max_horyzontal() const {
  return 180u;
}

utils::UInt utils::ProfileImpl::rotator_max_vertical() const {
  return 120u;
}

utils::UInt utils::ProfileImpl::rotator_min_horyzontal() const {
  return 0u;
}

utils::UInt utils::ProfileImpl::rotator_min_vertical() const {
  return 0u;
}

const utils::String& utils::ProfileImpl::server_address() const {
  return utils::String("");
}

utils::UInt utils::ProfileImpl::server_port() const {
  return 0;
}
