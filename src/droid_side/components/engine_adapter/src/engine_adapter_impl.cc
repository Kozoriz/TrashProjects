#include "engine_adapter/engine_adapter_impl.h"
#include "utils/containers/string.h"
#include "utils/logger.h"

engine_adapter::EngineAdapterImpl::EngineAdapterImpl()
    : finalyzing_(false), current_state_(Direction::STOP) {}

engine_adapter::EngineAdapterImpl::~EngineAdapterImpl() {
  Join();
}

void engine_adapter::EngineAdapterImpl::SpinForward(
    const utils::UInt milliseconds) {
  current_state_ = Direction::FORWARD;
  move_value_ = milliseconds;
}

void engine_adapter::EngineAdapterImpl::SpinBack(
    const utils::UInt milliseconds) {
  current_state_ = Direction::BACK;
  move_value_ = milliseconds;
}

void engine_adapter::EngineAdapterImpl::SetAdapterSynchronizationBarrier(
    utils::synchronization::Barrier* barrier) {
  synchronization_barrier_ = barrier;
}

void engine_adapter::EngineAdapterImpl::Run() {
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
      default:
        break;
    }
  }
}

void engine_adapter::EngineAdapterImpl::Join() {
  finalyzing_ = true;
}

void engine_adapter::EngineAdapterImpl::OnSpinDone() {
  move_value_ = 0;
  current_state_ = Direction::STOP;
  synchronization_barrier_->Wait();
}

void engine_adapter::EngineAdapterImpl::SpinForwardLowLevel(
    const utils::UInt milliseconds) const {}

void engine_adapter::EngineAdapterImpl::SpinBackLowLevel(
    const utils::UInt milliseconds) const {}
