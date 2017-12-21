#include "servo_adapter/servo_adapter.h"

namespace servo_adapter {
class ServoAdapterImpl : public ServoAdapter {
 public:
  enum Position { HORIZONTAL, VERTICAL };

  ServoAdapterImpl(const Position pos);

  void ChangeAngle(const utils::Int angle_delta) override;
  void SetAngle(const utils::UInt new_angle) override;

 private:
  const Position position_;
  utils::Int current_angle_;
};
}
