#pragma once

#include "server_message_handler/message.h"
#include "utils/structures/position.h"

namespace mover {
enum class MoveType { INVALID_ENUM = -1, ROTATE, MOVE_FORWARD };

struct MoveMessage : public server_message_handler::Message {
  MoveType move_type_;
  /**
   * @brief value_ - angle/distace
   */
  utils::Int value_;
};
}
