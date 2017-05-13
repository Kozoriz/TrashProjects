#pragma once
#include "drone_mover/drone_mover.h"
#include "utils/profile.h"

namespace drone_mover {
class DroneMoverImpl : public DroneMover {
 public:
  DroneMoverImpl(const utils::Profile& settings);
  ~DroneMoverImpl();

  utils::Vector<messages::MoveMessage*> MakeMoveCommadns(
      const utils::positions::Location3& drone_dislocation,
      const utils::Vector<utils::positions::Location3>& way_points) override;

 private:
  const utils::Profile& settings_;
};
}
