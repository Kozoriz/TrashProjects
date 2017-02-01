#include "guide/guide.h"
#include "gmock/gmock.h"
namespace guide {

class MockGuide : public Guide {
 public:
  MOCK_METHOD0(foo,
      void());
};

}  // namespace guide
