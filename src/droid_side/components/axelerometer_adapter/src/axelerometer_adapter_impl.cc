#include "axelerometer_adapter/axelerometer_adapter_impl.h"
#include "utils/logger.h"

utils::positions::Incline
axelerometer_adapter::AxelerometerAdapterImpl::GetData() const {
  LOG_TRACE(logger::IN);

  utils::positions::Incline incl;
  return incl;

  LOG_TRACE(logger::OUT);
}
