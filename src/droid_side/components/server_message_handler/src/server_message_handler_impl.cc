#include "server_message_handler/server_message_handler_impl.h"
#include "utils/threads/synchronization/auto_lock.h"

#include "messages/sensor_data_message.h"
#include "utils/network/tcp_socket_client.h"

#include "utils/logger.h"

CREATE_LOGGER("ServerMessageHandler")

namespace server_message_handler {

namespace {
const utils::UInt process_messages_timeout = 1000u;
}

ServerMessageHandlerImpl::ServerMessageHandlerImpl(
    mover::Mover& mover,
    scanner::Scanner& scanner,
    const utils::Profile& settings)
    : mover_(mover)
    , scanner_(scanner)
    , server_socket_connection_(nullptr)
    , settings_(settings) {
  LOG_AUTO_TRACE();
  server_socket_connection_ = new utils::TcpSocketClient(
      settings_.server_address(), settings_.server_port());
}

ServerMessageHandlerImpl::~ServerMessageHandlerImpl() {
  LOG_AUTO_TRACE();
  if (server_socket_connection_) {
    delete server_socket_connection_;
  }
}

void ServerMessageHandlerImpl::SendMessageToServer(
    const messages::Message* message) {
  LOG_AUTO_TRACE();
  utils::synchronization::AutoLock auto_lock(messages_to_server_lock_);
  messages_to_server_.push(message);
}

void ServerMessageHandlerImpl::Run() {
  LOG_AUTO_TRACE();
  server_socket_connection_->Init();
  while (true) {
    utils::ByteArray raw_data;
    while (true) {
      // Receiving from server
      raw_data.resize(0);
      raw_data = server_socket_connection_->Receive();
      if (0 == raw_data.size()) {
        break;
      }
      messages::Message message(raw_data);
      switch (message.type()) {
        case messages::MessageType::MOVE: {
          mover_.OnMoveMessageReceived(messages::MoveMessage(raw_data));
          break;
        }
        case messages::MessageType::START_SCAN: {
          scanner_.OnScanningTriggered();
          break;
        }
        case messages::MessageType::STOP_PROGRAM: {
          LOG_DEBUG("STOP_PROGRAM message received");
          return;
        }
        default:
          LOG_WARN("Unknown message type received!");
          break;
      }
    }

    {
      utils::synchronization::AutoLock auto_lock(messages_to_server_lock_);
      while (!messages_to_server_.empty()) {
        const messages::SensorDataMessage* message =
            static_cast<const messages::SensorDataMessage*>(
                messages_to_server_.front());
        messages_to_server_.pop();
        // Sending to server
        server_socket_connection_->Send(message->ToRawData());
        delete message;
      }
    }
    LOG_DEBUG("Waiting next cycle for " << process_messages_timeout
                                        << " miliseconds.");
    wait_cond_var_.WaitFor(wait_lock_, process_messages_timeout);
  }
}

void ServerMessageHandlerImpl::Join() {}

#if defined(BUILD_TESTS)
utils::UInt ServerMessageHandlerImpl::get_messages_to_server_size() const {
  return messages_to_server_.size();
}

void ServerMessageHandlerImpl::set_socket(utils::SocketClient* new_socket) {
  if (server_socket_connection_) {
    delete server_socket_connection_;
  }
  server_socket_connection_ = new_socket;
}
#endif

}  // namespace server_message_handler
