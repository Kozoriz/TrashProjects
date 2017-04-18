#pragma once

#include "utils/structures/position.h"
#include "utils/structures/matrix3.h"

namespace snapshot_processor {
enum class Octal {
  // (1 if <0)
  // z,y,x = 000
  I = 0,
  // z,y,x = 001
  II = 1,
  III = 3,
  IV = 2,
  V = 4,
  VI = 5,
  VII = 7,
  VIII = 6
};
/**
 * @brief The Snapshot contains 8 3D matrixes(quadrants)
 * (x<0,y>0,z>0)(x>0,y<0,z>0)(x>0,y>0,z<0) e.g.
 */
class Snapshot {
 public:
  void AddPoint(const utils::positions::Location3& point);

 private:
  // X>0 Y>0 Z>0
  utils::structures::Matrix3 I_quadrant;
  // X<0
  utils::structures::Matrix3 II_quadrant;
  // X<0 Y<0
  utils::structures::Matrix3 III_quadrant;
  // Y<0
  utils::structures::Matrix3 IV_quadrant;
  // Z<0 (under I)
  utils::structures::Matrix3 V_quadrant;
  // X<0 Z<0 (under II)
  utils::structures::Matrix3 VI_quadrant;
  // X<0 Y<0 Z<0 (under III)
  utils::structures::Matrix3 VII_quadrant;
  // Y<0 Z<0 (under IV)
  utils::structures::Matrix3 VIII_quadrant;
};

}  // namespace snapshot_processor
