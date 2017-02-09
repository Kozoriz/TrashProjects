#pragma once

#include "utils/numbers.h"
#include "utils/containers/vector.h"

namespace utils {
class Socket {
 public:
  virtual void Send(const ByteArray& message) = 0;
  virtual const ByteArray& Receive() = 0;
};
}  // namespace utils
