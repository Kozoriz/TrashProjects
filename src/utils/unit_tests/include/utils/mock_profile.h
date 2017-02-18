#pragma once
#include "gmock/gmock.h"
#include "utils/profile.h"

namespace utils {

class MockProfile : public Profile {
 public:
  MOCK_CONST_METHOD0(mover_adapters_count, const utils::UInt());
};

}  // namespace utils
