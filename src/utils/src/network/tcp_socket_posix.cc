
#include "utils/network/tcp_socket.h"

namespace utils {
TcpSocket::TcpSocket(const utils::String& address, const UInt16 port)
    : address_(address), port_(port) {
  // TODO realyze with posiz socket?
}

TcpSocket::~TcpSocket() {}

void TcpSocket::Send(const ByteArray& message) {}

const ByteArray& TcpSocket::Receive() {}
}
