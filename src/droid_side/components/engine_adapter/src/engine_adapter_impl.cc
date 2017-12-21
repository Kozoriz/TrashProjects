#include "engine_adapter/engine_adapter_impl.h"
#include "utils/containers/string.h"
#include "utils/logger.h"

#include "utils/logger.h"
#include "utils/arduino_mmap_worker_singletone.h"

CREATE_LOGGER("EngineAdapter")

engine_adapter::EngineAdapterImpl::EngineAdapterImpl(const Position pos)
    : finalyzing_(false)
    , current_state_(Direction::STOP)
    , engine_position_(pos) {
  LOG_AUTO_TRACE();
}

engine_adapter::EngineAdapterImpl::~EngineAdapterImpl() {
  LOG_AUTO_TRACE();
  Join();
}

void engine_adapter::EngineAdapterImpl::SpinForward(
    const utils::UInt milliseconds) {
  LOG_AUTO_TRACE();
  current_state_ = Direction::FORWARD;
  move_value_ = milliseconds;
}

void engine_adapter::EngineAdapterImpl::SpinBack(
    const utils::UInt milliseconds) {
  LOG_AUTO_TRACE();
  current_state_ = Direction::BACK;
  move_value_ = milliseconds;
}

void engine_adapter::EngineAdapterImpl::SetAdapterSynchronizationBarrier(
    utils::synchronization::Barrier* barrier) {
  LOG_AUTO_TRACE();
  synchronization_barrier_ = barrier;
}

void engine_adapter::EngineAdapterImpl::Run() {
  LOG_AUTO_TRACE();
  while (!finalyzing_) {
    switch (current_state_) {
      case Direction::FORWARD: {
        SpinForwardLowLevel(move_value_);
        OnSpinDone();
        break;
      }
      case Direction::BACK: {
        SpinBackLowLevel(move_value_);
        OnSpinDone();
        break;
      }
      default: {
        OnSpinDone();
        break;
      }
    }
  }
}

void engine_adapter::EngineAdapterImpl::Join() {
  LOG_AUTO_TRACE();
  finalyzing_ = true;
}

void engine_adapter::EngineAdapterImpl::OnSpinDone() {
  LOG_AUTO_TRACE();
  move_value_ = 0;
  current_state_ = Direction::STOP;
  synchronization_barrier_->Wait();
}

void engine_adapter::EngineAdapterImpl::SpinForwardLowLevel(
    const utils::UInt milliseconds) const {
  LOG_AUTO_TRACE();
  utils::DroneAction current_action =
      utils::MmapWorker::getInstance()->GetCurrentAct();

  if ((utils::DroneAction::LEFT_TRACK == current_action &&
       Position::LEFT != engine_position_) ||
      (utils::DroneAction::RIGHT_TRACK == current_action &&
       Position::RIGHT != engine_position_)) {
    utils::MmapWorker::getInstance()->WriteNewStateToMap(
        utils::DroneAction::BOTH_TRACKS, milliseconds);
    return;
  }

  utils::DroneAction result_action = (Position::LEFT == engine_position_)
                                         ? utils::DroneAction::LEFT_TRACK
                                         : utils::DroneAction::RIGHT_TRACK;
  utils::MmapWorker::getInstance()->WriteNewStateToMap(result_action,
                                                       milliseconds);
}

void engine_adapter::EngineAdapterImpl::SpinBackLowLevel(
    const utils::UInt milliseconds) const {
  LOG_AUTO_TRACE();
}
