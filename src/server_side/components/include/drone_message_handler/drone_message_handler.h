#pragma once
#include "utils/threads/thread_runnable.h"
#include "messages/message.h"

namespace drone_message_handler {
class DroneMessageHandler : public utils::threads::ThreadRunnable {
 public:
  virtual void SendMessageToDroid(const messages::Message* message) = 0;
};
}
