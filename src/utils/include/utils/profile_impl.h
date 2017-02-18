#pragma once

#include "utils/containers/string.h"
#include "utils/profile.h"

namespace utils {
class ProfileImpl : public Profile {
 public:
  ProfileImpl(const utils::String& file_name);
  const utils::UInt mover_adapters_count() const override;
};
}
