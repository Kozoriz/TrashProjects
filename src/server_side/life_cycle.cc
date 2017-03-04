#include "life_cycle.h"
#include "utils/logger.h"

//#include "drone_message_handler/drone_message_handler_impl.h"
#include "components/drone_message_handler/include/drone_message_handler/drone_message_handler_impl.h"

#include "utils/containers/string.h"
#include "utils/profile_impl.h"

CREATE_LOGGER("Main")

#include "messages/move_message.h"

void LifeCycle::InitComponents() {
  LOG_AUTO_TRACE();

  const utils::String file_name = "enviroment_scanner_server.ini";
  settings_ = new utils::ProfileImpl(file_name);

  message_handler_ =
      new drone_message_handler::DroneMessageHandlerImpl(*settings_);
}

void LifeCycle::DeinitComponents() {
  LOG_AUTO_TRACE();
  delete message_handler_;

  delete settings_;
}

void LifeCycle::StartThreads() {
  LOG_AUTO_TRACE();
}

int LifeCycle::ListenToClient() {
  LOG_AUTO_TRACE();
  messages::Message* move =
      new messages::MoveMessage(messages::MoveType::ROTATE, 100u);
  messages::Message* scan =
      new messages::Message(messages::MessageType::START_SCAN);
  messages::Message* stop =
      new messages::Message(messages::MessageType::STOP_PROGRAM);

  message_handler_->SendMessageToDroid(move);
  message_handler_->SendMessageToDroid(scan);
//  message_handler_->SendMessageToDroid(stop);

  message_handler_->Run();
}
