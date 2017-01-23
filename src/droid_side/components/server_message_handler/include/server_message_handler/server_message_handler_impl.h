#include "server_message_handler/server_message_handler.h"

#include "mover/mover.h"
#include "scanner/scanner.h"
#include "utils/queue.h"
#include "utils/synchronization/lock.h"

namespace server_message_handler {
class ServerMessageHandlerImpl : public ServerMessageHandler {
 public:
  ServerMessageHandlerImpl(mover::Mover& mover, scanner::Scanner& scanner);
  void SendMessageToServer(const Message* message) override;
  void Run() override;

 private:
  utils::Queue<const Message*> messages_to_server_;
  utils::synchronization::Lock messages_to_server_lock_;

  mover::Mover& mover_;
  scanner::Scanner& scanner_;
};
}
