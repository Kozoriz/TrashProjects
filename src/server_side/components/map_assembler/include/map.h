#pragma once
#include "utils/structures/matrix3.h"

namespace map_assembler {
class Map {
public:
  void AddPoint(utils::positions::Location3& point) {
    storage_.AddPoint(point);
  }

  void ShiftMapToFirstQuadrant() {
    // find min x y z
    // add to every point
  }

private:
  utils::structures::Matrix3 storage_;
};
