#include "gtest/gtest.h"

#include "engine_adapter/mock_engine_adapter.h"
#include "mover/tank_track_mover.h"
#include "utils/async_waiter.h"
#include "utils/threads/thread.h"

#include "utils/mock_profile.h"

namespace test {
namespace mover_test {

using ::testing::_;
using ::testing::Return;

namespace {
const utils::Int negative_move_value = -10;
const utils::Int positive_move_value = 10;
// TODO use profiler
const utils::Float centimeters_per_second = 3.f;
const utils::Float angles_per_second = 3.f;

const utils::UInt default_waiting_timeout_ms = 300000;
}

class MoverImplTest : public ::testing::Test {
 public:
  MoverImplTest() {
    EXPECT_CALL(left_ea_, SetAdapterSynchronizationBarrier(_));
    EXPECT_CALL(right_ea_, SetAdapterSynchronizationBarrier(_));
    EXPECT_CALL(mock_settings_, mover_adapters_count())
        .WillRepeatedly(Return(0u));

    track_mover_ =
        new mover::TankTrackMover(left_ea_, right_ea_, mock_settings_);
    mover_thread_ = new utils::threads::Thread(*track_mover_);

    EXPECT_CALL(left_ea_, Run());
    EXPECT_CALL(right_ea_, Run());
    EXPECT_CALL(left_ea_, Join());
    EXPECT_CALL(right_ea_, Join());
  }
  ~MoverImplTest() {
    delete mover_thread_;
    delete track_mover_;
  }

 protected:
  utils::MockProfile mock_settings_;
  engine_adapter::MockEngineAdapter left_ea_;
  engine_adapter::MockEngineAdapter right_ea_;
  mover::TankTrackMover* track_mover_;
  utils::threads::Thread* mover_thread_;

  utils::TestAsyncWaiter waiter_;
};

TEST_F(MoverImplTest, Run_MoveForwardPositiveDistance_ForwardTwoAdapters) {
  const utils::Int milliseconds = positive_move_value / centimeters_per_second;
  mover::MoveMessage message(mover::MoveType::MOVE_FORWARD,
                             positive_move_value);

  EXPECT_CALL(left_ea_, SpinForward(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));
  EXPECT_CALL(right_ea_, SpinForward(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));

  mover_thread_->StartThread();
  track_mover_->OnMoveMessageReceived(message);
  waiter_.WaitFor(2, default_waiting_timeout_ms);
  mover_thread_->JoinThread();
}

TEST_F(MoverImplTest, Run_MoveForwardNegativeDistance_BackTwoAdapters) {
  const utils::Int milliseconds =
      -1 * negative_move_value / centimeters_per_second;
  mover::MoveMessage message(mover::MoveType::MOVE_FORWARD,
                             negative_move_value);

  EXPECT_CALL(left_ea_, SpinBack(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));
  EXPECT_CALL(right_ea_, SpinBack(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));

  mover_thread_->StartThread();
  track_mover_->OnMoveMessageReceived(message);
  waiter_.WaitFor(2, default_waiting_timeout_ms);
  mover_thread_->JoinThread();
}

TEST_F(MoverImplTest, Run_RotatePositiveValue_VersoVersaTwoAdapters) {
  const utils::Int milliseconds = positive_move_value / angles_per_second;
  mover::MoveMessage message(mover::MoveType::ROTATE, positive_move_value);

  EXPECT_CALL(left_ea_, SpinForward(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));
  EXPECT_CALL(right_ea_, SpinBack(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));

  mover_thread_->StartThread();
  track_mover_->OnMoveMessageReceived(message);
  waiter_.WaitFor(2, default_waiting_timeout_ms);
  mover_thread_->JoinThread();
}

TEST_F(MoverImplTest, Run_RotateNegativeDistance_VersoVersaTwoAdapters) {
  const utils::Int milliseconds = -1 * negative_move_value / angles_per_second;
  mover::MoveMessage message(mover::MoveType::ROTATE, negative_move_value);

  EXPECT_CALL(left_ea_, SpinBack(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));
  EXPECT_CALL(right_ea_, SpinForward(milliseconds))
      .WillOnce(utils::NotifyTestAsyncWaiter(&waiter_));

  mover_thread_->StartThread();
  track_mover_->OnMoveMessageReceived(message);
  waiter_.WaitFor(2, default_waiting_timeout_ms);
  mover_thread_->JoinThread();
}
}
}
