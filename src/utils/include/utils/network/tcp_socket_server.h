#pragma once

#include <boost/asio.hpp>

#include "utils/network/socket_server.h"

#include "utils/containers/map.h"
#include "utils/threads/thread.h"
#include "utils/pointers/shared_prt.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/containers/message_queue.h"

namespace utils {

typedef boost::asio::ip::tcp::socket BoostSocket;

class TcpSocketServer : public SocketServer {
 public:
  //  TODO If several clients will be supported
  //  typedef utils::Map<SharedPtr<threads::Thread>, SharedPtr<ClientSession> >
  //  ClientThreadsMap;

  TcpSocketServer(const utils::UInt16 port);
  ~TcpSocketServer();
  void Send(const ByteArray& message) override;
  const ByteArray& Receive() override;
  void AcceptClient() override;

 private:
  class ClientSession : public utils::threads::ThreadRunnable {
   public:
    ClientSession(utils::SharedPtr<BoostSocket>& socket,
                  TcpSocketServer& parent);
    void WriteDataToSocket(const ByteArray& message);
    const ByteArray& ReadDataFromSocket();

    void Run() override;
    void Join() override;

   private:
    utils::SharedPtr<BoostSocket> socket_;
    synchronization::AtomicBool finalyzing_;

    TcpSocketServer& parent_;

    ByteArray buffer_;
  };

  void OnMessageReceived(const ByteArray& message);

 private:
  const utils::UInt16 port_;
  //  ClientThreadsMap clients_map_;
  SharedPtr<ClientSession> client_;

  boost::asio::io_service boost_io_service_;
  boost::asio::ip::tcp::acceptor boost_acceptor_;

  //  MessageQueue<ByteArray> messages_from_client_;
};

}  // namespace utils
