
#include <boost/asio/basic_socket.hpp>

#include "utils/network/tcp_socket_server.h"

namespace utils {
TcpSocketServer::TcpSocketServer(const utils::String& address,
                                 const UInt16 port)
    : address_(address), port_(port) {
  // TODO realyze with posiz socket?
}

TcpSocketServer::~TcpSocketServer() {}

void TcpSocketServer::Send(const ByteArray& message) {}

const ByteArray& TcpSocketServer::Receive() {}
}
