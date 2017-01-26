#include "gtest/gtest.h"
namespace test {
namespace guide {
class GuideImplTest : public ::testing::Test {
 public:
  GuideImplTest() {}
  ~GuideImplTest() {}
};

TEST_F(GuideImplTest, Test) {
  ASSERT_TRUE(false);
}
}
}
