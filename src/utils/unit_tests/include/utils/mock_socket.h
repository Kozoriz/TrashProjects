#pragma once
#include "utils/network/socket.h"
#include "gmock/gmock.h"

namespace utils {

class MockSocket : public Socket {
 public:
  MOCK_METHOD1(Send, void(const ByteArray& message));
  MOCK_METHOD0(Receive, const utils::ByteArray&());
};

}  // namespace utils
