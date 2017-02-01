#include "server_message_handler/server_message_handler.h"
#include "gmock/gmock.h"
namespace server_message_handler {

class MockServerMessageHandler : public ServerMessageHandler {
 public:
  MOCK_METHOD1(SendMessageToServer,
      void(const Message* message));
};

}  // namespace server_message_handler
