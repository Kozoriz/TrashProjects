#pragma once
#include "utils/containers/vector.h"
#include "messages/move_message.h"
#include "utils/structures/position.h"

namespace drone_mover {
class DroneMover {
 public:
  virtual utils::Vector<messages::MoveMessage*> MakeMoveCommadns(
      const utils::positions::Location3& drone_dislocation,
      const utils::Vector<utils::positions::Location3>& way_points) = 0;
};
}
