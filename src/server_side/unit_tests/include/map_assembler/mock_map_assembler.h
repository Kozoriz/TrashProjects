#include "map_assembler/map_assembler.h"
#include "gmock/gmock.h"
namespace map_assembler {

class MockMapAssembler : public MapAssembler {
 public:
  MOCK_METHOD0(foo,
      void());
};

}  // namespace map_assembler
