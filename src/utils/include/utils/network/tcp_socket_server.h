#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include "utils/network/socket_server.h"

#include "utils/containers/map.h"
#include "utils/pointers/shared_prt.h"
#include "utils/pointers/unique_ptr.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/containers/message_queue.h"

namespace utils {

typedef boost::asio::ip::tcp::socket BoostSocket;
typedef MessageQueue<ByteArray> ServerMessageQueue;

class TcpSocketServer : public SocketServer {
 public:
  TcpSocketServer(const utils::UInt16 port);
  ~TcpSocketServer();
  void Send(const ByteArray& message) override;
  ByteArray Receive() override;
  void AcceptClient() override;
  void Init() override;

 private:
  class ClientSession {
   public:
    ClientSession(utils::SharedPtr<BoostSocket>& socket,
                  TcpSocketServer& parent);
    void WriteDataToSocket(const ByteArray& message);
    const ByteArray& ReadDataFromSocket();

   private:
    utils::SharedPtr<BoostSocket> socket_;
    synchronization::AtomicBool finalyzing_;

    TcpSocketServer& parent_;

    ByteArray buffer_;

    ServerMessageQueue messages_to_client_;
    ServerMessageQueue messages_from_client_;
  };

 private:
  const utils::UInt16 port_;
  SharedPtr<ClientSession> client_;

  boost::asio::io_service boost_io_service_;
  boost::asio::ip::tcp::acceptor boost_acceptor_;
};

}  // namespace utils
