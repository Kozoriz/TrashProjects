#pragma once
#include "gmock/gmock.h"
#include "utils/profile.h"

namespace utils {

class MockProfile : public Profile {
 public:
  MOCK_CONST_METHOD0(mover_adapters_count, utils::UInt());
  MOCK_CONST_METHOD0(engine_centimeters_per_second, utils::Float());
  MOCK_CONST_METHOD0(engine_angle_per_second, utils::Float());
  MOCK_CONST_METHOD0(rotator_max_horyzontal, utils::UInt());
  MOCK_CONST_METHOD0(rotator_max_vertical, utils::UInt());
  MOCK_CONST_METHOD0(rotator_min_horyzontal, utils::UInt());
  MOCK_CONST_METHOD0(rotator_min_vertical, utils::UInt());
  MOCK_CONST_METHOD0(server_address, const utils::String&());
  MOCK_CONST_METHOD0(server_port, utils::UInt());
};

}  // namespace utils
