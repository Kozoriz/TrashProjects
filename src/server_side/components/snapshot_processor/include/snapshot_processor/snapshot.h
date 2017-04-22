#pragma once

#include "utils/structures/position.h"
#include "utils/structures/matrix3.h"
#include "utils/pointers/unique_ptr.h"
#include "utils/pointers/shared_prt.h"

namespace snapshot_processor {
typedef utils::UniquePtr<utils::structures::Matrix3> QuadrantSPtr;
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
  Snapshot();
  void AddPoint(const utils::positions::Location3& point);
  void Clear();
  const utils::structures::Matrix3& GetQuadrant(Octal octal);

 private:
  // X>0 Y>0 Z>0
  QuadrantSPtr I_quadrant;
  // X<0
  QuadrantSPtr II_quadrant;
  // X<0 Y<0
  QuadrantSPtr III_quadrant;
  // Y<0
  QuadrantSPtr IV_quadrant;
  // Z<0 (under I)
  QuadrantSPtr V_quadrant;
  // X<0 Z<0 (under II)
  QuadrantSPtr VI_quadrant;
  // X<0 Y<0 Z<0 (under III)
  QuadrantSPtr VII_quadrant;
  // Y<0 Z<0 (under IV)
  QuadrantSPtr VIII_quadrant;
};

typedef utils::SharedPtr<Snapshot> SnapshotSPtr;

}  // namespace snapshot_processor
