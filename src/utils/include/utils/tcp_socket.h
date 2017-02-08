#pragma once

#include "utils/socket.h"
#include "utils/string.h"

namespace utils {
class TcpSocket : public Socket {
 public:
  TcpSocket(const utils::String& address, const utils::UInt16 port);
  ~TcpSocket();
  void Send(const ByteArray& message) override;
  const ByteArray& Receive() override;

 private:
  const utils::String address_;
  const utils::UInt16 port_;
};
}  // namespace utils
