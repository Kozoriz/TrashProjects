#include "axelerometer_adapter/axelerometer_adapter.h"
#include "gmock/gmock.h"
namespace axelerometer_adapter {

class MockAxelerometerAdapter : public AxelerometerAdapter {
 public:
  MOCK_CONST_METHOD0(GetData, utils::positions::Incline());
};

}  // namespace axelerometer_adapter
