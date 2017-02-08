#include "server_message_handler/server_message_handler_impl.h"
#include "utils/synchronization/auto_lock.h"

#include "scanner/sensor_data_message.h"
#include "utils/tcp_socket.h"

namespace server_message_handler {

ServerMessageHandlerImpl::ServerMessageHandlerImpl(mover::Mover& mover,
                                                   scanner::Scanner& scanner)
    : mover_(mover), scanner_(scanner), server_socket_(nullptr) {
  // TODO use profiler
  server_socket_ = new utils::TcpSocket("192.168.0.1", 10999);
}

ServerMessageHandlerImpl::~ServerMessageHandlerImpl() {
  if (server_socket_) {
    delete server_socket_;
  }
}

void ServerMessageHandlerImpl::SendMessageToServer(const Message* message) {
  utils::synchronization::AutoLock auto_lock(messages_to_server_lock_);
  messages_to_server_.push(message);
}

void ServerMessageHandlerImpl::Run() {
  while (true) {
    // Receiving from server
    const utils::ByteArray& raw_data = server_socket_->Receive();
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
        server_socket_->Send(message->ToRawData());
        delete message;
      }
    }
  }
}

}  // namespace server_message_handler
