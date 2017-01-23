#pragma once

#include "server_message_handler/message.h"
#include "utils/threads/thread_runnable.h"

namespace server_message_handler {
class ServerMessageHandler : public utils::threads::ThreadRunnable {
 public:
  virtual void SendMessageToServer(const Message* message) = 0;
};
}
