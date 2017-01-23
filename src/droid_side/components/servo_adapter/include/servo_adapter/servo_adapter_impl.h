#include "servo_adapter/servo_adapter.h"

namespace servo_adapter {
class ServoAdapterImpl : public ServoAdapter {
 public:
  void ChangeAngle(const utils::Int angle_delta) override;
  void SetAngle(const utils::UInt new_angle) override;
};
}
