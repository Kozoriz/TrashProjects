
#include <boost/asio.hpp>

#include "utils/network/tcp_socket_client.h"
#include "utils/threads/synchronization/conditional_variable.h"

#include "utils/logger.h"

CREATE_LOGGER("Utils")

namespace utils {
using namespace boost::asio::ip;

namespace {
// TODO use profile
const utils::UInt max_buffer_size = 5u;
// TODO use profile
const utils::UInt connect_waiting_timeout_ms = 5000u;
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
  EstabilishConnection();
}

void TcpSocketClient::Send(const ByteArray& message) {
  LOG_AUTO_TRACE();
  boost::asio::write(boost_socket_,
                     boost::asio::buffer(message, max_buffer_size));
}

const ByteArray& TcpSocketClient::Receive() {
  LOG_AUTO_TRACE();
  buffer_.clear();
  const size_t data_size = boost::asio::read(
      boost_socket_, boost::asio::buffer(buffer_, max_buffer_size));
  LOG_DEBUG("Read socket data lenght : " << buffer_.size());
  buffer_.resize(data_size);
  return buffer_;
}

void TcpSocketClient::EstabilishConnection() {
  LOG_AUTO_TRACE();
  const utils::String str_port = utils::ConvertToString(port_);
  tcp::resolver resolver(boost_io_service_);
  tcp::resolver::query resolver_query(address_, str_port);
  boost::system::error_code ec;
  tcp::resolver::iterator resolver_iterator;

  synchronization::Lock wait_lock;
  utils::synchronization::ConditionalVariable wait_cv;
  while (true) {
    LOG_DEBUG("Trying to resolve : " << address_ << ":" << str_port);
    resolver_iterator = resolver.resolve(resolver_query, ec);
    if (tcp::resolver::iterator() != resolver_iterator) {
      break;
    }
    LOG_DEBUG("Resolving failed : " << ec.message() << ". Wait for : "
                                    << connect_waiting_timeout_ms);
    wait_cv.WaitFor(wait_lock, connect_waiting_timeout_ms);
  }

  boost::asio::connect(boost_socket_, resolver_iterator);
  LOG_DEBUG("Client socket connected : " << address_ << ":" << str_port);
}
}
