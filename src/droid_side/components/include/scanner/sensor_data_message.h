#pragma once

#include "server_message_handler/message.h"
#include "utils/structures/position.h"

namespace scanner {
struct SensorDataMessage : public server_message_handler::Message {
  bool final_message_;
  utils::UInt distance_;
  utils::positions::Incline sensor_position_;
};
}
