#include "axelerometer_adapter/axelerometer_adapter_impl.h"
#include "utils/logger.h"

CREATE_LOGGER("AxelerometerAdapter")

utils::positions::Incline
axelerometer_adapter::AxelerometerAdapterImpl::GetData() const {
  LOG_AUTO_TRACE();

  utils::positions::Incline incl;
  return incl;
}
