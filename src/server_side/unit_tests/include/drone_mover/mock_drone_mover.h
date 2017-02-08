#include "drone_mover/drone_mover.h"
#include "gmock/gmock.h"
namespace drone_mover {

class MockDroneMover : public DroneMover {
 public:
  MOCK_METHOD0(foo, void());
};

}  // namespace drone_mover
