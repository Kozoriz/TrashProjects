#pragma once

#include "utils/structures/position.h"

namespace server_message_handler {
enum class MessageType { MOVE, SENSOR_DATA, START_SCAN, STOP_PROGRAM };
struct Message {
  MessageType type_;
};
}
