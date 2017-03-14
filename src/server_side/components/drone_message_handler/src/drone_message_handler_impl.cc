#include "drone_message_handler/drone_message_handler_impl.h"
#include "utils/logger.h"
#include "utils/network/tcp_socket_server.h"

#include "messages/message.h"
#include "messages/sensor_data_message.h"

CREATE_LOGGER("DroneMessageHandler")

namespace drone_message_handler {
namespace {
const utils::UInt process_messages_timeout = 1000u;
}

DroneMessageHandlerImpl::DroneMessageHandlerImpl(
    const utils::Profile& settings, MessageListener& message_listener)
    : settings_(settings)
    , message_listener_(message_listener)
    , socket_(new utils::TcpSocketServer(settings_.server_port()))
    , finalyzing_(false) {
  LOG_AUTO_TRACE();
}

DroneMessageHandlerImpl::~DroneMessageHandlerImpl() {
  LOG_AUTO_TRACE();
  delete socket_;
}

void DroneMessageHandlerImpl::Run() {
  LOG_AUTO_TRACE();

  socket_->Init();
  socket_->AcceptClient();

  while (!finalyzing_) {
    utils::synchronization::AutoLock auto_lock(messages_lock_);
    while (!messages_to_client_.IsEmpty()) {
      const messages::Message* message = messages_to_client_.GetMessage();
      socket_->Send(message->ToRawData());
      delete message;
    }

    utils::ByteArray raw_data;
    while (true) {
      raw_data = socket_->Receive();
      if (raw_data.empty()) {
        break;
      }
      messages::Message message(raw_data);
      switch (message.type()) {
        case messages::MessageType::SENSOR_DATA: {
          messages::SensorDataMessage sd_message(raw_data);
          if (sd_message.IsFinal()) {
            message_listener_.OnFinalMessageReceived();
          } else {
            message_listener_.OnDataMessageReceived(sd_message);
          }
          break;
        }
        default: {
          LOG_WARN("Unknown message type received!");
          break;
        }
      }
    }

    utils::synchronization::Lock wait_lock;
    utils::synchronization::ConditionalVariable wait_cv;
    wait_cv.WaitFor(wait_lock, process_messages_timeout);
  }
}

void DroneMessageHandlerImpl::Join() {
  LOG_AUTO_TRACE();
  finalyzing_ = true;
}

void DroneMessageHandlerImpl::SendMessageToDroid(
    const messages::Message* message) {
  LOG_AUTO_TRACE();
  utils::synchronization::AutoLock auto_lock(messages_lock_);
  if (!finalyzing_) {
    messages_to_client_.PushMessage(message);
  }
}
#if defined(BUILD_TESTS)
void DroneMessageHandlerImpl::set_socket(utils::SocketServer* socket) {
  LOG_AUTO_TRACE();
  socket_ = socket;
}
#endif
}
