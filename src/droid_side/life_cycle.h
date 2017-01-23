#pragma once

#include "axelerometer_adapter/axelerometer_adapter.h"
#include "engine_adapter/engine_adapter.h"
#include "mover/mover.h"
#include "scanner/scanner.h"
#include "sensor_adapter/sensor_adapter.h"
#include "server_message_handler/server_message_handler.h"
#include "servo_adapter/servo_adapter.h"

#include "utils/threads/thread.h"

class LifeCycle {
 public:
  void InitComponents();
  void DeinitComponents();
  void StartThreads();
  int ListenToServer();

 private:
  server_message_handler::ServerMessageHandler* message_handler_;

  mover::Mover* mover_;
  // For tank tracks need only 2 engines
  engine_adapter::EngineAdapter* left_engine_;
  engine_adapter::EngineAdapter* right_engine_;

  scanner::Scanner* scanner_;
  sensor_adapter::SensorAdapter* sensor_;
  // Need 2 servo engines
  servo_adapter::ServoAdapter* x_servo_;
  servo_adapter::ServoAdapter* y_servo_;
  axelerometer_adapter::AxelerometerAdapter* axelerometer_;

  utils::threads::Thread* message_handler_thread_;
  utils::threads::Thread* mover_thread_;
  utils::threads::Thread* scanner_thread_;
};
