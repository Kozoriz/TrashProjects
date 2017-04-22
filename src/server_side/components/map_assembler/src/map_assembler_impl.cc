#include "map_assembler/map_assembler_impl.h"

namespace map_assembler {
MapAssemblerImpl::MapAssemblerImpl(const utils::Profile& settings)
    : settings_(settings) {}
MapAssemblerImpl::~MapAssemblerImpl() {}

void MapAssemblerImpl::AttachSnapshotToMap(
    utils::SharedPtr<snapshot_processor::Snapshot> snapshot,
    utils::positions::Location3 dislocation) {
  for (int octal = 0; octal < 7; ++octal) {
    const utils::structures::Matrix3& quadrant =
        snapshot->GetQuadrant(static_cast<snapshot_processor::Octal>(octal));
    for (auto point : quadrant) {
      storage_.AddPoint(point + dislocation);
    }
  }
  NormalizeGlobalMap();
}

const Map& MapAssemblerImpl::GetActualMap() const {
  return storage_;
}

void MapAssemblerImpl::NormalizeGlobalMap() {
  utils::Int min_x = 0;
  utils::Int min_y = 0;
  utils::Int min_z = 0;
  std::for_each(storage_.begin(),
                storage_.end(),
                [=, &min_x, &min_y, &min_z](utils::positions::Location3 point) {
                  if (point.x_ < min_x) {
                    min_x = point.x_;
                  }
                  if (point.y_ < min_y) {
                    min_y = point.y_;
                  }
                  if (point.z_ < min_z) {
                    min_z = point.z_;
                  }
                });
}

}  // namespace map_assembler
