#pragma once

#include "utils/containers/vector.h"
#include "utils/numbers.h"

namespace utils {
class Socket {
 public:
  virtual void Send(const ByteArray& message) = 0;
  virtual const ByteArray& Receive() = 0;
};
}  // namespace utils
