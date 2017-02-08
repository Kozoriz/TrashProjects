#include "engine_adapter/engine_adapter.h"
#include "gmock/gmock.h"
namespace engine_adapter {

class MockEngineAdapter : public EngineAdapter {
 public:
  MOCK_CONST_METHOD1(SpinForward, void(const utils::UInt milliseconds));
  MOCK_CONST_METHOD1(SpinBack, void(const utils::UInt milliseconds));
};

}  // namespace engine_adapter
