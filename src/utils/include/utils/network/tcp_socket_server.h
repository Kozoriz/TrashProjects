#pragma once

#include "utils/containers/string.h"
#include "utils/network/socket_server.h"

namespace utils {
class TcpSocketServer : public Socket {
 public:
  TcpSocketServer(const utils::String& address, const utils::UInt16 port);
  ~TcpSocketServer();
  void Send(const ByteArray& message) override;
  const ByteArray& Receive() override;

 private:
  const utils::String address_;
  const utils::UInt16 port_;
};
}  // namespace utils
