#pragma once
#include "drone_mover/drone_mover.h"
#include "utils/profile.h"

namespace drone_mover {
class DroneMoverImpl : public DroneMover {
 public:
  DroneMoverImpl(const utils::Profile& settings);
  ~DroneMoverImpl();

 private:
  const utils::Profile& settings_;
};
}
