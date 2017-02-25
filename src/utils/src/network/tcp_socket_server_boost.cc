
#include <boost/asio/basic_socket.hpp>

#include "utils/network/tcp_socket_server.h"

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
    , boost_acceptor_(boost_io_service_, tcp::endpoint(tcp::v4(), port_)) {}

TcpSocketServer::~TcpSocketServer() {}

void TcpSocketServer::Send(const ByteArray& message) {
  client_->WriteDataToSocket(message);
}

const ByteArray& TcpSocketServer::Receive() {
  return client_->ReadDataFromSocket();
}

void TcpSocketServer::AcceptClient() {
  SharedPtr<BoostSocket> socket(
      utils::make_shared<BoostSocket>(boost_io_service_));
  client_ = utils::make_shared<ClientSession>(socket, *this);
  boost_acceptor_.accept(*socket);

  // SharedPtr<threads::Thread>
  // thread(utils::make_shared<threads::Thread>(*session));
  // clients_map_.insert(ClientThreadsMap::value_type(thread, session));
  // thread->StartThread();
}

void TcpSocketServer::OnMessageReceived(const ByteArray& message) {
  //    messages_from_client_.PushMessage(message);
}

TcpSocketServer::ClientSession::ClientSession(
    utils::SharedPtr<BoostSocket>& socket, TcpSocketServer& parent)
    : socket_(socket), finalyzing_(false), parent_(parent_) {}

/*
 *
 *     {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock->read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

 *
 *
 */

void TcpSocketServer::ClientSession::WriteDataToSocket(
    const ByteArray& message) {
  boost::asio::write(*socket_, boost::asio::buffer(message, max_buffer_size));
}

const ByteArray& TcpSocketServer::ClientSession::ReadDataFromSocket() {
  boost::system::error_code error;
  size_t length =
      socket_->read_some(boost::asio::buffer(buffer_, max_buffer_size), error);
  return buffer_;
}

void TcpSocketServer::ClientSession::Run() {}

void TcpSocketServer::ClientSession::Join() {}
}
