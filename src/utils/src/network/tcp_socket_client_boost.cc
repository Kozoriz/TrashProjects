
#include <boost/asio.hpp>

#include "utils/network/tcp_socket_client.h"

namespace utils {
using namespace boost::asio::ip;

TcpSocketClient::TcpSocketClient(const utils::String& address,
                                 const UInt16 port)
    : address_(address), port_(port), boost_socket_(boost_io_service_) {
  tcp::resolver resolver(boost_io_service_);
  tcp::resolver::query resolver_query("host", "Server");
  tcp::resolver::iterator resolver_iterator = resolver.resolve(resolver_query);
  // ???????/
  boost::asio::connect(boost_socket_, resolver_iterator);
}

TcpSocketClient::~TcpSocketClient() {}

void TcpSocketClient::Send(const ByteArray& message) {}

const ByteArray& TcpSocketClient::Receive() {}
}
