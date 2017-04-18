#pragma once

#include "utils/numbers.h"

namespace utils {
namespace positions {
/**
 * @brief The Incline struct - angles cant be more than 359 = 9bits
 */
struct Incline {
  utils::Int16 alpha_ = 0;
  utils::Int16 beta_ = 0;
};

struct Location2 {
  utils::Int x_ = 0;
  utils::Int y_ = 0;

  bool operator==(const Location2& other) const {
    return other.x_ == x_ && other.y_ == y_;
  }
};

struct Location3 {
  utils::Int x_ = 0;
  utils::Int y_ = 0;
  utils::Int z_ = 0;

  bool operator==(const Location3& other) const {
    return other.x_ == x_ && other.y_ == y_ && other.z_ ==   z_;
  }
};
}
}
