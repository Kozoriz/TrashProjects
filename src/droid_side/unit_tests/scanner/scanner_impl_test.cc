#include "gtest/gtest.h"

#include "axelerometer_adapter/mock_axelerometer_adapter.h"
#include "scanner/scanner_impl.h"
#include "sensor_adapter/mock_sensor_adapter.h"
#include "server_message_handler/mock_server_message_handler.h"
#include "servo_adapter/mock_servo_adapter.h"

#include "scanner/sensor_data_message.h"

#include "utils/async_waiter.h"
#include "utils/threads/thread.h"

namespace test {
namespace scanner_test {
static utils::UInt counter_ = 0;
using ::testing::Return;
using ::testing::_;
using ::testing::SaveArg;

class ScannerImplTest : public ::testing::Test {
 public:
  ScannerImplTest()
      : scanner_(mock_sensor_adapter_,
                 mock_horizontal_servo_adapter_,
                 mock_vertical_servo_adapter_,
                 mock_axelerometer_adapter_)
      , scanner_thread_(scanner_) {
    scanner_.SetServerMessageHandler(&mock_server_message_handler_);
  }
  ~ScannerImplTest() {}

 protected:
  server_message_handler::MockServerMessageHandler mock_server_message_handler_;
  sensor_adapter::MockSensorAdapter mock_sensor_adapter_;
  servo_adapter::MockServoAdapter mock_horizontal_servo_adapter_;
  servo_adapter::MockServoAdapter mock_vertical_servo_adapter_;
  axelerometer_adapter::MockAxelerometerAdapter mock_axelerometer_adapter_;

  scanner::ScannerImpl scanner_;
  utils::threads::Thread scanner_thread_;
};

MATCHER_P(ExpectFinalMessage, is_final, "") {
  const scanner::SensorDataMessage* message_ptr =
      static_cast<const scanner::SensorDataMessage*>(arg);
  const utils::Byte first_byte = message_ptr->ToRawData()[0];
  const bool final = static_cast<bool>((first_byte & 0x10) >> 4);
  return is_final == final;
}

TEST_F(ScannerImplTest, Run_FullCycle_CorrectCountOfCalls) {
  // TODO get from profile
  const utils::UInt max_alpha = 179u + 1;
  const utils::UInt max_beta = 180u + 1;

  utils::TestAsyncWaiter waiter;

  EXPECT_CALL(mock_sensor_adapter_, GetSensorData())
      .Times(max_alpha * max_beta);
  EXPECT_CALL(mock_axelerometer_adapter_, GetData())
      .Times(max_alpha * max_beta);
  EXPECT_CALL(mock_server_message_handler_,
              SendMessageToServer(ExpectFinalMessage(false)))
      .Times(max_alpha * max_beta);
  EXPECT_CALL(mock_server_message_handler_,
              SendMessageToServer(ExpectFinalMessage(true)))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter));

  scanner_.OnScanningTriggered();
  scanner_thread_.StartThread();
  waiter.WaitFor(1, 3000);
  scanner_thread_.JoinThread();
}
}
}
