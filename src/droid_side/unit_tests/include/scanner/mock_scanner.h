#pragma once

#include "gmock/gmock.h"
#include "scanner/scanner.h"
namespace scanner {

class MockScanner : public Scanner {
 public:
  MOCK_METHOD0(OnScanningTriggered, void());
  MOCK_METHOD1(
      SetServerMessageHandler,
      void(server_message_handler::ServerMessageHandler* message_handler));
  MOCK_METHOD0(Run, void());
  MOCK_METHOD0(Join, void());
};

}  // namespace scanner
