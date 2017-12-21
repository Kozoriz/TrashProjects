#pragma once

#include "utils/containers/vector.h"
#include "utils/structures/position.h"
#include "map_assembler/map_assembler.h"

namespace map_detalization_analyzer {
typedef utils::Vector<utils::positions::Location3> PointsArray;
class MapDetalizationAnalyzer {
 public:
  virtual PointsArray ProcessAnalisationPoints(
      const map_assembler::Map& actual_map) = 0;
};
}
