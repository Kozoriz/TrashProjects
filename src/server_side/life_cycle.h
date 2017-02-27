#pragma once

#include "drone_message_handler/drone_message_handler.h"

//#include "utils/threads/thread.h"

#include "utils/profile.h"

class LifeCycle {
 public:
  void InitComponents();
  void DeinitComponents();
  void StartThreads();
  int ListenToClient();

 private:
  utils::Profile* settings_;

  drone_message_handler::DroneMessageHandler* message_handler_;
};
