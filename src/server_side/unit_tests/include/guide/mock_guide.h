#include "gmock/gmock.h"
#include "guide/guide.h"
namespace guide {

class MockGuide : public Guide {
 public:
  MOCK_METHOD0(foo, void());
};

}  // namespace guide
