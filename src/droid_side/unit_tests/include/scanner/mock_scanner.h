#include "scanner/scanner.h"
#include "gmock/gmock.h"
namespace scanner {

class MockScanner : public Scanner {
 public:
  MOCK_METHOD0(OnScanningTriggered,
      void());
};

}  // namespace scanner
