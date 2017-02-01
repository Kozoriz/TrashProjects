#include "snapshot_processor/snapshot_processor.h"
#include "gmock/gmock.h"
namespace snapshot_processor {

class MockSnapshotProcessor : public SnapshotProcessor {
 public:
  MOCK_METHOD0(foo,
      void());
};

}  // namespace snapshot_processor
