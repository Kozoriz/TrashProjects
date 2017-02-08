#include "gtest/gtest.h"

#include "engine_adapter/mock_engine_adapter.h"
#include "mover/tank_track_mover.h"

namespace test {
namespace mover_test {

namespace  {
const utils::Int negative_move_value = -10;
const utils::Int positive_move_value = 10;
// TODO use profiler
const utils::Float centimeters_per_second = 3.f;
const utils::Float angles_per_second = 3.f;
}

class MoverImplTest : public ::testing::Test {
 public:
  MoverImplTest() : track_mover_(left_ea_, right_ea_) {}
  ~MoverImplTest() {}
protected:
  engine_adapter::MockEngineAdapter left_ea_;
  engine_adapter::MockEngineAdapter right_ea_;
    mover::TankTrackMover track_mover_;
};

TEST_F(MoverImplTest, DISABLED_Run_MoveForwardPositiveDistance_ForwardTwoAdapters) {
    const utils::Int milliseconds = positive_move_value / centimeters_per_second;
    mover::MoveMessage message(mover::MoveType::MOVE_FORWARD, positive_move_value);

    track_mover_.OnMoveMessageReceived(message);

    EXPECT_CALL(left_ea_, SpinForward(milliseconds));
    EXPECT_CALL(right_ea_, SpinForward(milliseconds));
    track_mover_.Run();
}

TEST_F(MoverImplTest, DISABLED_Run_MoveForwardNegativeDistance_BackTwoAdapters) {
    const utils::Int milliseconds = -1 *  negative_move_value / centimeters_per_second;
    mover::MoveMessage message(mover::MoveType::MOVE_FORWARD, negative_move_value);

    track_mover_.OnMoveMessageReceived(message);

    EXPECT_CALL(left_ea_, SpinBack(milliseconds));
    EXPECT_CALL(right_ea_, SpinBack(milliseconds));
    track_mover_.Run();
}

TEST_F(MoverImplTest, DISABLED_Run_RotatePositiveValue_VersoVersaTwoAdapters) {
    const utils::Int milliseconds = positive_move_value / angles_per_second;
    mover::MoveMessage message(mover::MoveType::ROTATE, positive_move_value);

    track_mover_.OnMoveMessageReceived(message);

    EXPECT_CALL(left_ea_, SpinForward(milliseconds));
    EXPECT_CALL(right_ea_, SpinBack(milliseconds));
    track_mover_.Run();
}

TEST_F(MoverImplTest, DISABLED_Run_RotateNegativeDistance_VersoVersaTwoAdapters) {
    const utils::Int milliseconds = -1 *  negative_move_value / angles_per_second;
    mover::MoveMessage message(mover::MoveType::ROTATE, negative_move_value);

    track_mover_.OnMoveMessageReceived(message);

    EXPECT_CALL(left_ea_, SpinBack(milliseconds));
    EXPECT_CALL(right_ea_, SpinForward(milliseconds));
    track_mover_.Run();
}

}
}
