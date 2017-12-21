#pragma once

#include "messages/message.h"
#include "utils/threads/thread_runnable.h"

namespace server_message_handler {
class ServerMessageHandler : public utils::threads::ThreadRunnable {
 public:
  virtual void SendMessageToServer(const messages::Message* message) = 0;
};
}
