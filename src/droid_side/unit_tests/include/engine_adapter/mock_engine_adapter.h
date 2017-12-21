#include "engine_adapter/engine_adapter.h"
#include "gmock/gmock.h"
namespace engine_adapter {

class MockEngineAdapter : public EngineAdapter {
 public:
  MOCK_METHOD1(SpinForward, void(const utils::UInt milliseconds));
  MOCK_METHOD1(SpinBack, void(const utils::UInt milliseconds));
  MOCK_METHOD1(SetAdapterSynchronizationBarrier,
               void(utils::synchronization::Barrier* barrier));
  MOCK_METHOD0(Run, void());
  MOCK_METHOD0(Join, void());
};

}  // namespace engine_adapter
