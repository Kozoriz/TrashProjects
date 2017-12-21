#include "gmock/gmock.h"
#include "servo_adapter/servo_adapter.h"
namespace servo_adapter {

class MockServoAdapter : public ServoAdapter {
 public:
  MOCK_METHOD1(ChangeAngle, void(const utils::Int angle_delta));
  MOCK_METHOD1(SetAngle, void(const utils::Int new_angle));
};

}  // namespace servo_adapter
