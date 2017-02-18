#pragma once

#include "utils/numbers.h"

namespace utils {

class Profile {
 public:
  virtual const utils::UInt mover_adapters_count() const = 0;
};
}
