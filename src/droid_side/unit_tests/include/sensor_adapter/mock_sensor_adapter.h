#include "gmock/gmock.h"
#include "sensor_adapter/sensor_adapter.h"
namespace sensor_adapter {

class MockSensorAdapter : public SensorAdapter {
 public:
  MOCK_CONST_METHOD0(GetSensorData, utils::UInt());
};

}  // namespace sensor_adapter
