#include "life_cycle.h"
#include "utils/logger.h"

#include "axelerometer_adapter/axelerometer_adapter_impl.h"
#include "engine_adapter/engine_adapter_impl.h"
#include "mover/tank_track_mover.h"
#include "scanner/scanner_impl.h"
#include "sensor_adapter/lidar_lite_3_adapter.h"
#include "servo_adapter/servo_adapter_impl.h"

#include "server_message_handler/server_message_handler_impl.h"

#include "utils/containers/string.h"
#include "utils/profile_impl.h"

CREATE_LOGGER("Main")

void LifeCycle::InitComponents() {
  LOG_AUTO_TRACE();

  const utils::String file_name = "client_side_settings.ini";
  settings_ = new utils::ProfileImpl(file_name);

#ifdef AXELEROMETER_INCLUDED
#error "Need to implement another impl"
#else
  axelerometer_ = new axelerometer_adapter::AxelerometerAdapterImpl();
#endif
  sensor_ = new sensor_adapter::LidarLite3Adapter();
  x_servo_ = new servo_adapter::ServoAdapterImpl();
  y_servo_ = new servo_adapter::ServoAdapterImpl();
  scanner_ =
      new scanner::ScannerImpl(*sensor_, *x_servo_, *y_servo_, *axelerometer_);

  left_engine_ = new engine_adapter::EngineAdapterImpl();
  right_engine_ = new engine_adapter::EngineAdapterImpl();
  mover_ = new mover::TankTrackMover(*left_engine_, *right_engine_, *settings_);

  message_handler_ =
      new server_message_handler::ServerMessageHandlerImpl(*mover_, *scanner_);
}

void LifeCycle::DeinitComponents() {
  LOG_AUTO_TRACE();
  delete scanner_;
  delete axelerometer_;
  delete x_servo_;
  delete y_servo_;
  delete sensor_;

  delete mover_;
  delete left_engine_;
  delete right_engine_;

  delete message_handler_;

  delete settings_;
}

void LifeCycle::StartThreads() {
  LOG_AUTO_TRACE();
  mover_thread_ = new utils::threads::Thread(*mover_);
  scanner_thread_ = new utils::threads::Thread(*scanner_);

  mover_thread_->StartThread();
  scanner_thread_->StartThread();
}

int LifeCycle::ListenToServer() {
  LOG_AUTO_TRACE();
  message_handler_->Run();
}
