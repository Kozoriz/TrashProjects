#include "map_assembler/map_assembler_impl.h"
#include "utils/logger.h"
#include "utils/containers/string.h"
#include "utils/file_system.h"
#include "utils/date_time.h"

CREATE_LOGGER("MapAssembler")
namespace map_assembler {
namespace {}  // namespace

MapAssemblerImpl::MapAssemblerImpl(const utils::Profile& settings)
    : settings_(settings) {}
MapAssemblerImpl::~MapAssemblerImpl() {}

void MapAssemblerImpl::AttachSnapshotToMap(
    utils::SharedPtr<snapshot_processor::Snapshot> snapshot,
    utils::positions::Location3 dislocation) {
  LOG_AUTO_TRACE();
  for (int octal = 0; octal < 7; ++octal) {
    const utils::structures::Matrix3& quadrant =
        snapshot->GetQuadrant(static_cast<snapshot_processor::Octal>(octal));
    for (auto point : quadrant) {
      utils::positions::Location3 temp = snapshot->ShiftToOctal(
          point, static_cast<snapshot_processor::Octal>(octal));
      storage_.AddPoint(temp + dislocation);
    }
  }
  LOG_DEBUG("SnapshotAttached");
  //  Must be used only in case needed shifting map to first quadrant
  //  NormalizeGlobalMap();
}

const Map& MapAssemblerImpl::GetActualMap() const {
  LOG_AUTO_TRACE();
  return storage_;
}

void MapAssemblerImpl::SaveMapFile() const {
    using namespace utils::file_system;
    LOG_AUTO_TRACE();

    const utils::String name =
        utils::date_time::GetDateTimeString("Map_%Y_%m_%d_%I_%M_%S");
    File file(name);
    file.Open(File::OpenMode::Write);

    for(auto point : storage_) {
        file.WriteLine(point.ToString());
    }

    file.Close();
}

void MapAssemblerImpl::NormalizeGlobalMap() {
  LOG_AUTO_TRACE();
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
  // TODO shift all points for minimal values p.x_+abs(min_x)
}

}  // namespace map_assembler
