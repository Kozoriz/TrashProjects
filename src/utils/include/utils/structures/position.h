#pragma once

#include "utils/numbers.h"

namespace utils {
namespace positions {
/**
 * @brief The Incline struct - angles cant be more than 359 = 9bits
 */
struct Incline {
  utils::UInt16 alpha_ = 0;
  utils::UInt16 beta_ = 0;
};

struct Location2 {
  utils::Int x_ = 0;
  utils::Int y_ = 0;
};

struct Location3 {
  utils::Int x_ = 0;
  utils::Int y_ = 0;
  utils::Int z_ = 0;
};
}
}
