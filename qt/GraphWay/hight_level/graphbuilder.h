#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <string>
#include <vector>

#include "data_types/graph.h"
#include "low_level/umlbuilder.h"

class GraphBuilder {
 public:
  typedef std::vector<std::vector<std::string> > RawImportData;
  GraphBuilder();

  void BuildGraphFromRawData(const RawImportData& data);
  const Graph& graph();

 private:
  Graph* graph_;

  void CreateEndpoints(const GraphBuilder::RawImportData& data);
  void LinkEndpoints(const GraphBuilder::RawImportData& data);
  void MakeUmlFile();
};

#endif  // GRAPHBUILDER_H
