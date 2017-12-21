#include "gmock/gmock.h"
#include "map_detalization_analyzer/map_detalization_analyzer.h"
namespace map_detalization_analyzer {

class MockMapDetalizationAnalyzer : public MapDetalizationAnalyzer {
 public:
  MOCK_METHOD0(foo, void());
};

}  // namespace map_detalization_analyzer
