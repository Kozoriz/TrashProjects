#include "gtest/gtest.h"

#include "server_message_handler/server_message_handler_impl.h"

#include "mover/mock_mover.h"
#include "scanner/mock_scanner.h"
#include "utils/mock_profile.h"
#include "utils/mock_socket.h"

namespace test {
namespace server_message_handler_test {

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;

namespace {
const utils::String empty_server_address = "";
const utils::UInt empty_server_port = 0;
}

class ServerMessageHandlerImplTest : public ::testing::Test {
 public:
  ServerMessageHandlerImplTest() : mock_socket_(new utils::MockSocket) {
    EXPECT_CALL(mock_settings_, server_address())
        .WillOnce(ReturnRef(empty_server_address));
    EXPECT_CALL(mock_settings_, server_port())
        .WillOnce(Return(empty_server_port));
    server_message_handler_ =
        new server_message_handler::ServerMessageHandlerImpl(
            mock_mover_, mock_scanner_, mock_settings_);
    server_message_handler_->set_socket(mock_socket_);

    ::testing::Mock::AllowLeak(mock_socket_);
  }
  ~ServerMessageHandlerImplTest() {
    delete server_message_handler_;
  }

 protected:
  server_message_handler::ServerMessageHandlerImpl* server_message_handler_;
  mover::MockMover mock_mover_;
  scanner::MockScanner mock_scanner_;
  utils::MockProfile mock_settings_;
  // Will be deleted in server_message_handler
  utils::MockSocket* mock_socket_;
};

TEST_F(ServerMessageHandlerImplTest, Run_SeveralMessagesToServer_SendAll) {
  using namespace server_message_handler;
  const utils::UInt messages_count = 5u;
  ASSERT_EQ(0u, server_message_handler_->get_messages_to_server_size());

  for (int i = 0; i < messages_count; ++i) {
    server_message_handler_->SendMessageToServer(
        new messages::Message(messages::MessageType::SENSOR_DATA));
  }

  ASSERT_EQ(messages_count,
            server_message_handler_->get_messages_to_server_size());

  // Will go to default section
  utils::ByteArray raw_empty_message;
  utils::ByteArray raw_exit_message =
      messages::Message(messages::MessageType::STOP_PROGRAM).ToRawData();

  EXPECT_CALL(*mock_socket_, Receive())
      .WillOnce(ReturnRef(raw_empty_message))
      .WillOnce(ReturnRef(raw_exit_message));

  EXPECT_CALL(*mock_socket_, Send(_)).Times(messages_count);

  server_message_handler_->Run();

  ASSERT_EQ(0u, server_message_handler_->get_messages_to_server_size());
}

TEST_F(ServerMessageHandlerImplTest, Run_MoveFromServer_CorrectCall) {
  using namespace server_message_handler;

  utils::ByteArray raw_move_message = messages::Message(messages::MessageType::MOVE).ToRawData();
  utils::ByteArray raw_exit_message =
      messages::Message(messages::MessageType::STOP_PROGRAM).ToRawData();

  EXPECT_CALL(*mock_socket_, Receive())
      .WillOnce(ReturnRef(raw_move_message))
      .WillOnce(ReturnRef(raw_exit_message));
  EXPECT_CALL(mock_mover_, OnMoveMessageReceived(_));

  EXPECT_CALL(*mock_socket_, Send(_)).Times(0);

  server_message_handler_->Run();
}

TEST_F(ServerMessageHandlerImplTest, Run_StartScanFromServer_CorrectCall) {
  using namespace server_message_handler;

  utils::ByteArray raw_scan_message =
      messages::Message(messages::MessageType::START_SCAN).ToRawData();
  utils::ByteArray raw_exit_message =
      messages::Message(messages::MessageType::STOP_PROGRAM).ToRawData();

  EXPECT_CALL(*mock_socket_, Receive())
      .WillOnce(ReturnRef(raw_scan_message))
      .WillOnce(ReturnRef(raw_exit_message));
  EXPECT_CALL(mock_scanner_, OnScanningTriggered());

  EXPECT_CALL(*mock_socket_, Send(_)).Times(0);

  server_message_handler_->Run();
}
}
}
