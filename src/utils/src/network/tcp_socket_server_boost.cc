
#include <boost/asio/basic_socket.hpp>

#include "utils/network/tcp_socket_server.h"

#include "utils/logger.h"

CREATE_LOGGER("Utils")

namespace utils {

namespace {
// TODO use profile
const utils::UInt max_buffer_size = 5u;
// TODO use profile
const utils::UInt connect_waiting_timeout_ms = 5000u;
}

using namespace boost::asio::ip;

TcpSocketServer::TcpSocketServer(const UInt16 port)
    : port_(port)
    , boost_acceptor_(boost_io_service_, tcp::endpoint(tcp::v4(), port_)) {
  LOG_AUTO_TRACE();
}

TcpSocketServer::~TcpSocketServer() {
  LOG_AUTO_TRACE();
}

void TcpSocketServer::Send(const ByteArray& message) {
  LOG_AUTO_TRACE();
  client_->WriteDataToSocket(message);
}

ByteArray TcpSocketServer::Receive() {
  LOG_AUTO_TRACE();
  return client_->ReadDataFromSocket();
}

void TcpSocketServer::AcceptClient() {
  LOG_AUTO_TRACE();
  SharedPtr<BoostSocket> socket(
      utils::make_shared<BoostSocket>(boost_io_service_));
  client_ = utils::make_shared<ClientSession>(socket, *this);
  LOG_DEBUG("Accepting client via " << port_ << " port.");
  boost_acceptor_.accept(*socket);

  // SharedPtr<threads::Thread>
  // thread(utils::make_shared<threads::Thread>(*session));
  // clients_map_.insert(ClientThreadsMap::value_type(thread, session));
  // thread->StartThread();
}

void TcpSocketServer::Init() {
  LOG_AUTO_TRACE();
}

TcpSocketServer::ClientSession::ClientSession(
    utils::SharedPtr<BoostSocket>& socket, TcpSocketServer& parent)
    : socket_(socket), finalyzing_(false), parent_(parent_) {
  LOG_AUTO_TRACE();
}

void TcpSocketServer::ClientSession::WriteDataToSocket(
    const ByteArray& message) {
  LOG_AUTO_TRACE();
  const size_t sent_data_size = boost::asio::write(
      *socket_, boost::asio::buffer(message, max_buffer_size));
  LOG_DEBUG("Sent data size : " << sent_data_size);
}

const ByteArray& TcpSocketServer::ClientSession::ReadDataFromSocket() {
  LOG_AUTO_TRACE();
//  boost::system::error_code error;
  buffer_.clear();
  buffer_.resize(max_buffer_size);
  size_t length =
      socket_->receive(boost::asio::buffer(buffer_, max_buffer_size));
  return buffer_;
}
}
