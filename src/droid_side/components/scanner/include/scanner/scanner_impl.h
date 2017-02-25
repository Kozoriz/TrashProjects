#pragma once

#include "axelerometer_adapter/axelerometer_adapter.h"
#include "scanner/scanner.h"
#include "scanner/sensor_data_message.h"
#include "sensor_adapter/sensor_adapter.h"
#include "servo_adapter/servo_adapter.h"
#include "utils/profile.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/threads/synchronization/lock.h"
#include "utils/threads/synchronization/conditional_variable.h"

namespace server_message_handler {
class ServerMessageHandler;
}

namespace scanner {
class ScannerImpl : public Scanner {
 public:
  ScannerImpl(
      const sensor_adapter::SensorAdapter& sensor_adapter,
      servo_adapter::ServoAdapter& x_servo_adapter,
      servo_adapter::ServoAdapter& y_servo_adapter,
      const axelerometer_adapter::AxelerometerAdapter& axelerometer_adapter,
      const utils::Profile& settings);
  ~ScannerImpl();
  void OnScanningTriggered() override;
  void Run() override;
  void Join() override;
  void SetServerMessageHandler(
      server_message_handler::ServerMessageHandler* message_handler);

 private:
  SensorDataMessage MakeServerMessage(
      utils::UInt distance, utils::positions::Incline axelerometer_data);
  scanner::SensorDataMessage MakeFinalMessage();
  void SendDataToServer(const SensorDataMessage& message) const;

 private:
  const sensor_adapter::SensorAdapter& sensor_;
  /**
   * @brief x_rotator_ - horizontal sensor rotator
   */
  servo_adapter::ServoAdapter& x_rotator_;
  /**
   * @brief y_rotator_ - vertical sensor rotator
   */
  servo_adapter::ServoAdapter& y_rotator_;
  const axelerometer_adapter::AxelerometerAdapter& axelerometer_adapter_;

  server_message_handler::ServerMessageHandler* message_handler_;

  utils::synchronization::AtomicBool is_scanning_allowed_;
  utils::synchronization::AtomicBool finalyzing_;

  utils::positions::Incline current_position_;

  utils::synchronization::Lock finalyzing_lock_;
  utils::synchronization::ConditionalVariable triggering_wait_cond_var_;


  const utils::Profile& settings_;
};
}
