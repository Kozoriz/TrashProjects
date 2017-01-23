#include "engine_adapter/engine_adapter_impl.h"
#include "utils/logger.h"
#include "utils/string.h"

void engine_adapter::EngineAdapterImpl::SpinForward(
    const utils::UInt milliseconds) const {
  LOG_TRACE(logger::IN);
  LOG_DEBUG(utils::String("Time : ") << milliseconds);
  // TODO process with API
  LOG_TRACE(logger::OUT);
}

void engine_adapter::EngineAdapterImpl::SpinBack(
    const utils::UInt milliseconds) const {
  LOG_TRACE(logger::IN);
  LOG_DEBUG(utils::String("Time : ") << milliseconds);
  // TODO process with API
  LOG_TRACE(logger::OUT);
}
