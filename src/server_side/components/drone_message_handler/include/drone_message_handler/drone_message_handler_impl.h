#pragma once
#include "drone_message_handler/drone_message_handler.h"
#include "utils/network/socket_server.h"
#include "utils/containers/message_queue.h"
#include "messages/message.h"

#include "utils/profile.h"

namespace drone_message_handler {

class DroneMessageHandlerImpl : public DroneMessageHandler {
 public:
  DroneMessageHandlerImpl(const utils::Profile& settings);
  ~DroneMessageHandlerImpl();
  void Run() override;
  void Join() override;
  void SendMessageToDroid(const messages::Message* message) override;


#if defined(BUILD_TESTS)
  void set_socket(utils::SocketServer* socket);
#endif
 private:
  utils::SocketServer* socket_;
  utils::MessageQueue<const messages::Message*> messages_to_client_;

  const utils::Profile& settings_;
};
}
