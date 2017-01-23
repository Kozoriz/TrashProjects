#pragma once
#include "drone_message_handler/drone_message_handler.h"
namespace drone_message_handler {
class DroneMessageHandlerImpl : public DroneMessageHandler {
 public:
  DroneMessageHandlerImpl();
  ~DroneMessageHandlerImpl();
};
}
