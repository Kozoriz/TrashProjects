#pragma once

namespace snapshot_processor {
class Snapshot;
}

namespace map_assembler {
class Map;
class MapAssembler {
 public:
  virtual void AttachSnapshotToMap(
      const snapshot_processor::Snapshot& snapshot) = 0;
  virtual const Map& GetActualMap() const = 0;
};
}
