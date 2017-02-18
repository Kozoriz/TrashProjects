#pragma once

#include "utils/containers/string.h"
#include "utils/network/socket_client.h"

#include <boost/asio.hpp>

namespace utils {
class TcpSocketClient : public SocketClient {
 public:
  TcpSocketClient(const utils::String& address, const UInt8 port);
  ~TcpSocketClient();
  void Send(const ByteArray& message) override;
  const ByteArray& Receive() override;
  void Init() override;

 private:
  const utils::String address_;
  const utils::UInt8 port_;
  ByteArray buffer_;

  boost::asio::io_service boost_io_service_;
  boost::asio::ip::tcp::socket boost_socket_;
};
}  // namespace utils
