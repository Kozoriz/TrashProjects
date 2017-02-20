#include "sensor_adapter/lidar_lite_3_adapter.h"

#include "utils/logger.h"

CREATE_LOGGER("SensorAdapter")

utils::UInt sensor_adapter::LidarLite3Adapter::GetSensorData() const {
  LOG_AUTO_TRACE();
}

sensor_adapter::LidarLite3Adapter::LidarLite3Adapter() {
  LOG_AUTO_TRACE();
  // TODO process with API
}
