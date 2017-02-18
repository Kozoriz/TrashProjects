#pragma once
#include "drone_message_handler/drone_message_handler.h"
#include "utils/network/socket_client.h"

namespace drone_message_handler {
class DroneMessageHandlerImpl : public DroneMessageHandler {
 public:
  DroneMessageHandlerImpl();
  ~DroneMessageHandlerImpl();
//  void Run() override;
//  void SendMessageToDroid() override;
#if defined(BUILD_TESTS)
  void set_socket(utils::SocketClient* socket);
#endif
 private:
  utils::SocketClient* socket_;
};
}
