#include "server_message_handler/server_message_handler_impl.h"
#include "utils/threads/synchronization/auto_lock.h"

#include "scanner/sensor_data_message.h"
#include "utils/network/tcp_socket_client.h"

namespace server_message_handler {

ServerMessageHandlerImpl::ServerMessageHandlerImpl(
    mover::Mover& mover,
    scanner::Scanner& scanner,
    const utils::Profile& settings)
    : mover_(mover)
    , scanner_(scanner)
    , server_socket_connection_(nullptr)
    , settings_(settings) {
  server_socket_connection_ = new utils::TcpSocketClient(
      settings_.server_address(), settings_.server_port());
}

ServerMessageHandlerImpl::~ServerMessageHandlerImpl() {
  if (server_socket_connection_) {
    delete server_socket_connection_;
  }
}

void ServerMessageHandlerImpl::SendMessageToServer(const Message* message) {
  utils::synchronization::AutoLock auto_lock(messages_to_server_lock_);
  messages_to_server_.push(message);
}

void ServerMessageHandlerImpl::Run() {
  server_socket_connection_->Init();
  while (true) {
    // Receiving from server
    const utils::ByteArray& raw_data = server_socket_connection_->Receive();
    Message message(raw_data);
    switch (message.type()) {
      case MessageType::MOVE: {
        mover_.OnMoveMessageReceived(mover::MoveMessage(raw_data));
        break;
      }
      case MessageType::START_SCAN: {
        scanner_.OnScanningTriggered();
        break;
      }
      case MessageType::STOP_PROGRAM: {
        return;
      }
      default:
        // LOG ERROR
        break;
    }
    {
      utils::synchronization::AutoLock auto_lock(messages_to_server_lock_);
      while (!messages_to_server_.empty()) {
        const scanner::SensorDataMessage* message =
            static_cast<const scanner::SensorDataMessage*>(
                messages_to_server_.front());
        messages_to_server_.pop();
        // Sending to server
        server_socket_connection_->Send(message->ToRawData());
        delete message;
      }
    }
  }
}

void ServerMessageHandlerImpl::Join() {}

}  // namespace server_message_handler
