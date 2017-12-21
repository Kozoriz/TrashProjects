#include "gmock/gmock.h"
#include "snapshot_processor/snapshot_processor.h"
namespace snapshot_processor {

class MockSnapshotProcessor : public SnapshotProcessor {
 public:
  MOCK_METHOD0(foo, void());
};

}  // namespace snapshot_processor
