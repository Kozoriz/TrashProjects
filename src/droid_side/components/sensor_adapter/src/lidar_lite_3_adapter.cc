#include "sensor_adapter/lidar_lite_3_adapter.h"

#include "utils/logger.h"

#include "utils/arduino_mmap_worker_singletone.h"

CREATE_LOGGER("SensorAdapter")

utils::Int sensor_adapter::LidarLite3Adapter::GetSensorData() const {
  LOG_AUTO_TRACE();
  utils::MmapWorker::getInstance()->WriteNewStateToMap(utils::DroneAction::SCAN,
                                                       0);
  return utils::MmapWorker::getInstance()->GetCurrentActData();
}

sensor_adapter::LidarLite3Adapter::LidarLite3Adapter() {
  LOG_AUTO_TRACE();
}
