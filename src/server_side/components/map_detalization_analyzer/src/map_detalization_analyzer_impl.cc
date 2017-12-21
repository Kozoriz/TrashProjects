#include "map_detalization_analyzer/map_detalization_analyzer_impl.h"
#include "utils/logger.h"

CREATE_LOGGER("mapDetalisationAnalyzer")

namespace map_detalization_analyzer {
MapDetalizationAnalyzerImpl::MapDetalizationAnalyzerImpl(
    const utils::Profile& settings)
    : settings_(settings) {
  LOG_AUTO_TRACE();
}
MapDetalizationAnalyzerImpl::~MapDetalizationAnalyzerImpl() {
  LOG_AUTO_TRACE();
}

PointsArray MapDetalizationAnalyzerImpl::ProcessAnalisationPoints(
    const map_assembler::Map& actual_map) {
  LOG_AUTO_TRACE();
  // TODO
  return PointsArray();
}
}
