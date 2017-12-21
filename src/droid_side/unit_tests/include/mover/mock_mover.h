#pragma once

#include "gmock/gmock.h"
#include "mover/mover.h"
namespace mover {

class MockMover : public Mover {
 public:
  MOCK_METHOD1(OnMoveMessageReceived,
               void(const messages::MoveMessage& message));
  MOCK_METHOD0(Run, void());
  MOCK_METHOD0(Join, void());
};

}  // namespace mover
