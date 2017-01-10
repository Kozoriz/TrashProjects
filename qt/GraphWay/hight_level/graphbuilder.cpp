#include "hight_level/graphbuilder.h"
#include "data_types/endpoint.h"
#include "logger.h"

GraphBuilder::GraphBuilder() : graph_(new Graph) {}

void GraphBuilder::BuildGraphFromRawData(
    const GraphBuilder::RawImportData& data) {
  LOG_MESSAGE("GraphBuilder::BuildGraph");
  if (0 == data.size()) {
    LOG_MESSAGE("GraphBuilder::BuildGraph::EmptyData");
    return;
  }
  graph_->clean();
  CreateEndpoints(data);
  LinkEndpoints(data);
  MakeUmlFile();
}

const Graph& GraphBuilder::graph() {
  return *graph_;
}

void GraphBuilder::CreateEndpoints(const GraphBuilder::RawImportData& data) {
  LOG_MESSAGE("GraphBuilder::CreateEndpoints");
  for (size_t i = 0; i < data.size(); ++i) {
    const std::string name = data[i][0];
    LOG_MESSAGE("Make endpoint with name : " + name);
    Endpoint* ep = new Endpoint(name);
    graph_->AddEndpoint(ep);
  }
}

void GraphBuilder::LinkEndpoints(const GraphBuilder::RawImportData& data) {
  LOG_MESSAGE("GraphBuilder::LinkEndpoints");
  for (size_t row = 0; row < data.size(); ++row) {
    Endpoint* current_ep = graph_->GetEndpointByName(data[row][0]);
    for (size_t dist_i = row + 1, neigh_i = row; dist_i < data[row].size();
         ++dist_i, ++neigh_i) {
      const uint32_t dist = atoi(data[row][dist_i].c_str());
      if (dist > 0) {
        Endpoint* neighbor_ep = graph_->GetEndpointByName(data[neigh_i][0]);
        current_ep->AddNeighbor(neighbor_ep, dist);
      }
    }
  }
}

void GraphBuilder::MakeUmlFile() {
  typedef std::vector<Endpoint*> EndpointsArray;

  UmlBuilder uml("uml.plantuml");

  const EndpointsArray& endpoints = graph_->endpoints();
  for (size_t i = 0; i < endpoints.size(); ++i) {
    Endpoint* current_ep = endpoints[i];
    uml.AddClass(current_ep->name());
    for (auto& pair : current_ep->neighbors()) {
      EndpointsArray::const_iterator neigh_it =
          std::find(endpoints.begin(), endpoints.end(), pair.first);
      EndpointsArray::const_iterator current_it =
          std::find(endpoints.begin(), endpoints.end(), current_ep);
      if (neigh_it < current_it) {
        // Already added
        continue;
      }
      uml.AddLink(
          current_ep->name(), pair.first->name(), std::to_string(pair.second));
    }
  }
}
