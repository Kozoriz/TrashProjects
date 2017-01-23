#pragma once

#include "utils/numbers.h"

namespace utils {
namespace positions {

struct Incline {
  utils::UInt alpha_;
  utils::UInt beta_;
};

struct Location2 {
  utils::Int x_;
  utils::Int y_;
};

struct Location3 {
  utils::Int x_;
  utils::Int y_;
  utils::Int z_;
};
}
}
