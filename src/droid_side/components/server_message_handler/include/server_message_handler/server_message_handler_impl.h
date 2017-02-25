#include "server_message_handler/server_message_handler.h"

#include "mover/mover.h"
#include "scanner/scanner.h"
#include "scanner/sensor_data_message.h"
#include "utils/containers/queue.h"
#include "utils/network/socket_client.h"
#include "utils/threads/synchronization/conditional_variable.h"

#include "utils/containers/vector.h"
#include "utils/profile.h"

namespace server_message_handler {
class ServerMessageHandlerImpl : public ServerMessageHandler {
 public:
  ServerMessageHandlerImpl(mover::Mover& mover,
                           scanner::Scanner& scanner,
                           const utils::Profile& settings);
  virtual ~ServerMessageHandlerImpl();
  void SendMessageToServer(const Message* message) override;
  void Run() override;
  void Join() override;

 private:
  utils::Queue<const Message*> messages_to_server_;
  utils::synchronization::Lock messages_to_server_lock_;

  mover::Mover& mover_;
  scanner::Scanner& scanner_;
  // TODO investigate testing without using of pointer
  utils::SocketClient* server_socket_connection_;
  const utils::Profile& settings_;

  utils::synchronization::Lock wait_lock_;
  utils::synchronization::ConditionalVariable wait_cond_var_;

#if defined(BUILD_TESTS)
 public:
  utils::UInt get_messages_to_server_size() const {
    return messages_to_server_.size();
  }
  void set_socket(utils::SocketClient* new_socket) {
    if (server_socket_connection_) {
      delete server_socket_connection_;
    }
    server_socket_connection_ = new_socket;
  }
#endif
};
}
