#pragma once
#include "map_assembler/map_assembler.h"
#include "utils/profile.h"
namespace map_assembler {
class MapAssemblerImpl : public MapAssembler {
 public:
  MapAssemblerImpl(const utils::Profile& settings);
  ~MapAssemblerImpl();

  void AttachSnapshotToMap(
      utils::SharedPtr<snapshot_processor::Snapshot> snapshot,
      utils::positions::Location3 dislocation) override;
  const Map& GetActualMap() const override;
  void SaveMapFile() const override;

 private:
  /**
   * @brief NormalizeGlobalMap - shifts map to Ist quadrant
   */
  void NormalizeGlobalMap();

 private:
  const utils::Profile& settings_;
  Map storage_;
};
}  // namespace map_assembler
