#include "gmock/gmock.h"
#include "server_message_handler/server_message_handler.h"
namespace server_message_handler {

class MockServerMessageHandler : public ServerMessageHandler {
 public:
  MOCK_METHOD1(SendMessageToServer, void(const Message* message));
  MOCK_METHOD0(Run, void());
  MOCK_METHOD0(Join, void());
};

}  // namespace server_message_handler
