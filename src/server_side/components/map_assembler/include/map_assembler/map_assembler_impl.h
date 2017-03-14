#pragma once
#include "map_assembler/map_assembler.h"
#include "utils/profile.h"
namespace map_assembler {
class MapAssemblerImpl : public MapAssembler {
 public:
  MapAssemblerImpl(const utils::Profile& settings);
  ~MapAssemblerImpl();

  void AttachSnapshotToMap(
      const snapshot_processor::Snapshot& snapshot) override;
  const Map& GetActualMap() const override;

 private:
  const utils::Profile& settings_;
};
}  // namespace map_assembler
