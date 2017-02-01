#include "mover/mover.h"
#include "gmock/gmock.h"
namespace mover {

class MockMover : public Mover {
 public:
  MOCK_METHOD1(OnMoveMessageReceived,
      void(const MoveMessage* message));
};

}  // namespace mover
