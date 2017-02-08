#include "server_message_handler/server_message_handler.h"

#include "mover/mover.h"
#include "scanner/scanner.h"
#include "scanner/sensor_data_message.h"
#include "utils/queue.h"
#include "utils/socket.h"
#include "utils/synchronization/lock.h"

#include "utils/vector.h"

namespace server_message_handler {
class ServerMessageHandlerImpl : public ServerMessageHandler {
 public:
  ServerMessageHandlerImpl(mover::Mover& mover, scanner::Scanner& scanner);
  virtual ~ServerMessageHandlerImpl();
  void SendMessageToServer(const Message* message) override;
  void Run() override;

 private:
  utils::Queue<const Message*> messages_to_server_;
  utils::synchronization::Lock messages_to_server_lock_;

  mover::Mover& mover_;
  scanner::Scanner& scanner_;
  // TODO investigate testing without using of pointer
  utils::Socket* server_socket_;

#if defined(BUILD_TESTS)
 public:
  utils::UInt get_messages_to_server_size() const {
    return messages_to_server_.size();
  }
  void set_socket(utils::Socket* new_socket) {
    if (server_socket_) {
      delete server_socket_;
    }
    server_socket_ = new_socket;
  }
#endif
};
}
