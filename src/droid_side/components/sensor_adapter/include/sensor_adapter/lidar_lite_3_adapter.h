#include "sensor_adapter/sensor_adapter.h"

namespace sensor_adapter {
class LidarLite3Adapter : public SensorAdapter {
 public:
  LidarLite3Adapter();
  utils::Int GetSensorData() const override;
};
}
