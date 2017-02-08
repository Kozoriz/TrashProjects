#include "gmock/gmock.h"
#include "map_assembler/map_assembler.h"
namespace map_assembler {

class MockMapAssembler : public MapAssembler {
 public:
  MOCK_METHOD0(foo, void());
};

}  // namespace map_assembler
