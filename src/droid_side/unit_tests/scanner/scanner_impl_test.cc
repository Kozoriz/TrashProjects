#include "gtest/gtest.h"

#include "axelerometer_adapter/mock_axelerometer_adapter.h"
#include "scanner/scanner_impl.h"
#include "sensor_adapter/mock_sensor_adapter.h"
#include "server_message_handler/mock_server_message_handler.h"
#include "servo_adapter/mock_servo_adapter.h"

#include "messages/sensor_data_message.h"

#include "utils/async_waiter.h"
#include "utils/mock_profile.h"
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
                 mock_axelerometer_adapter_,
                 mock_settings_)
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
  utils::MockProfile mock_settings_;

  scanner::ScannerImpl scanner_;
  utils::threads::Thread scanner_thread_;
};

MATCHER_P(ExpectFinalMessage, is_final, "") {
  const messages::SensorDataMessage* message_ptr =
      static_cast<const messages::SensorDataMessage*>(arg);
  const utils::Byte first_byte = message_ptr->ToRawData()[0];
  const bool final = static_cast<bool>((first_byte & 0x10) >> 4);
  return is_final == final;
}

TEST_F(ScannerImplTest, Run_FullCycle_CorrectCountOfCalls) {
  const utils::UInt max_alpha = 10;
  const utils::UInt max_beta = 10;
  const utils::UInt expected_calls_count = (max_alpha + 1) * (max_beta + 1);

  EXPECT_CALL(mock_settings_, rotator_max_horyzontal())
      .WillOnce(Return(max_alpha));
  EXPECT_CALL(mock_settings_, rotator_max_vertical())
      .WillOnce(Return(max_beta));
  EXPECT_CALL(mock_settings_, rotator_min_horyzontal()).WillOnce(Return(0));
  EXPECT_CALL(mock_settings_, rotator_min_vertical()).WillOnce(Return(0));

  utils::TestAsyncWaiter waiter;

  EXPECT_CALL(mock_horizontal_servo_adapter_, SetAngle(_));
  EXPECT_CALL(mock_vertical_servo_adapter_, SetAngle(_)).Times(max_alpha + 1);
  EXPECT_CALL(mock_vertical_servo_adapter_, ChangeAngle(_))
      .Times(expected_calls_count);
  EXPECT_CALL(mock_horizontal_servo_adapter_, ChangeAngle(_))
      .Times(max_alpha + 1);

  EXPECT_CALL(mock_sensor_adapter_, GetSensorData())
      .Times(expected_calls_count);
  EXPECT_CALL(mock_axelerometer_adapter_, GetData())
      .Times(expected_calls_count);
  EXPECT_CALL(mock_server_message_handler_,
              SendMessageToServer(ExpectFinalMessage(false)))
      .Times(expected_calls_count);
  EXPECT_CALL(mock_server_message_handler_,
              SendMessageToServer(ExpectFinalMessage(true)))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter));

  scanner_thread_.StartThread();
  scanner_.OnScanningTriggered();
  waiter.WaitFor(1, 3000);
  scanner_thread_.JoinThread();
}
}
}
