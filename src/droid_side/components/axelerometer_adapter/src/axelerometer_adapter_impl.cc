#include "axelerometer_adapter/axelerometer_adapter_impl.h"
#include "utils/logger.h"

utils::positions::Incline
axelerometer_adapter::AxelerometerAdapterImpl::GetData() const {
  LOG_TRACE(logger::IN);

  utils::positions::Incline incl;
  incl.alpha_ = 0;
  incl.beta_ = 0;
  return incl;

  LOG_TRACE(logger::OUT);
}
