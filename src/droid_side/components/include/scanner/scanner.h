#pragma once

#include "utils/structures/position.h"
#include "utils/threads/thread_runnable.h"

namespace server_message_handler {
class ServerMessageHandler;
}

namespace scanner {
class Scanner : public utils::threads::ThreadRunnable {
 public:
  virtual void OnScanningTriggered() = 0;
  virtual void SetServerMessageHandler(
      server_message_handler::ServerMessageHandler* message_handler) = 0;
};
}
