#pragma once
#include "map_detalization_analyzer/map_detalization_analyzer.h"
#include "utils/profile.h"

namespace map_detalization_analyzer {
class MapDetalizationAnalyzerImpl : public MapDetalizationAnalyzer {
 public:
  MapDetalizationAnalyzerImpl(const utils::Profile& settings);
  ~MapDetalizationAnalyzerImpl();

  PointsArray ProcessAnalisationPoints(
      const map_assembler::Map& actual_map) override;

 private:
  const utils::Profile& settings_;
};
}
