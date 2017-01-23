#include "server_message_handler/server_message_handler_impl.h"
#include "utils/synchronization/auto_lock.h"

#include "scanner/sensor_data_message.h"

server_message_handler::ServerMessageHandlerImpl::ServerMessageHandlerImpl(
    mover::Mover& mover, scanner::Scanner& scanner)
    : mover_(mover), scanner_(scanner) {}

void server_message_handler::ServerMessageHandlerImpl::SendMessageToServer(
    const server_message_handler::Message* message) {
  utils::synchronization::AutoLock auto_lock(messages_to_server_lock_);
  messages_to_server_.push(message);
}

void server_message_handler::ServerMessageHandlerImpl::Run() {
  while (true) {
    /*
     * TODO
     * Check socket for messages
     * receive messages, sort by type
     */
    Message* message = new Message;  // get this message from socket
    switch (message->type_) {
      case MessageType::MOVE: {
        mover_.OnMoveMessageReceived(static_cast<mover::MoveMessage*>(message));
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

    while (!messages_to_server_.empty()) {
      const scanner::SensorDataMessage* message =
          static_cast<const scanner::SensorDataMessage*>(
              messages_to_server_.front());
      messages_to_server_.pop();
      /* TODO
       * send @message via socket
       */
      delete message;
    }
  }
}
