#pragma once

#include "snapshot_processor/snapshot.h"
#include "utils/pointers/shared_prt.h"
#include "utils/structures/matrix3.h"

namespace map_assembler {
typedef utils::structures::Matrix3 Map;
class MapAssembler {
 public:
  virtual void AttachSnapshotToMap(
      utils::SharedPtr<snapshot_processor::Snapshot> snapshot,
      utils::positions::Location3 dislocation) = 0;
  virtual const Map& GetActualMap() const = 0;
  virtual void SaveMapFile() const = 0;
};
}
