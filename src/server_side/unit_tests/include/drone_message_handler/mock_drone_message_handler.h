#include "drone_message_handler/drone_message_handler.h"
#include "gmock/gmock.h"
namespace drone_message_handler {

class MockDroneMessageHandler : public DroneMessageHandler {
 public:
  MOCK_METHOD0(foo, void());
};

}  // namespace drone_message_handler
