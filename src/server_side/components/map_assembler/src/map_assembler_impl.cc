#include "map_assembler/map_assembler_impl.h"

namespace map_assembler {
MapAssemblerImpl::MapAssemblerImpl(const utils::Profile& settings)
    : settings_(settings) {}
MapAssemblerImpl::~MapAssemblerImpl() {}

void MapAssemblerImpl::AttachSnapshotToMap(
    const snapshot_processor::Snapshot& snapshot) {}

const Map& MapAssemblerImpl::GetActualMap() const {}
}  // namespace map_assembler
