
#include <boost/asio.hpp>

#include "utils/network/tcp_socket_client.h"

#include "utils/logger.h"

CREATE_LOGGER("Utils")

namespace utils {
using namespace boost::asio::ip;

namespace {
const utils::UInt max_buffer_size = 5u;
}

TcpSocketClient::TcpSocketClient(const utils::String& address, const UInt8 port)
    : address_(address), port_(port), boost_socket_(boost_io_service_) {
  LOG_AUTO_TRACE();
}

TcpSocketClient::~TcpSocketClient() {
  LOG_AUTO_TRACE();
  boost_socket_.close();
}

void TcpSocketClient::Init() {
  LOG_AUTO_TRACE();
  const utils::String str_port = utils::ConvertToString(port_);
  tcp::resolver resolver(boost_io_service_);
  tcp::resolver::query resolver_query(address_, str_port);
  tcp::resolver::iterator resolver_iterator = resolver.resolve(resolver_query);
  boost::asio::connect(boost_socket_, resolver_iterator);
  LOG_DEBUG("Client socket connected : " << address_ << ":" << str_port);
}
void TcpSocketClient::Send(const ByteArray& message) {
  LOG_AUTO_TRACE();
  boost::asio::write(boost_socket_,
                     boost::asio::buffer(message, message.size()));
}

const ByteArray& TcpSocketClient::Receive() {
  LOG_AUTO_TRACE();
  buffer_.clear();
  boost::asio::read(boost_socket_,
                    boost::asio::buffer(buffer_, max_buffer_size));
  LOG_DEBUG("Read socket data lenght : " << buffer_.size());
  return buffer_;
}
}
