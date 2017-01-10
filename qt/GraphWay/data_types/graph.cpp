#include "graph.h"

Graph::Graph() {}

Graph::~Graph() {
  for (size_t i = 0; i < endpoints_.size(); ++i) {
    delete endpoints_[i];
  }
  endpoints_.clear();
}

void Graph::AddEndpoint(Endpoint* ep) {
  endpoints_.push_back(ep);
}

const std::vector<Endpoint*>& Graph::endpoints() const {
  return endpoints_;
}

Endpoint* Graph::GetEndpointByName(const std::__cxx11::string& name) const {
  for (size_t i = 0; i < endpoints_.size(); ++i) {
    if (endpoints_[i]->name() == name) {
      return endpoints_[i];
    }
  }
  return NULL;
}

std::vector<std::string> Graph::EndpointsNames() const {
  std::vector<std::string> names;
  for (size_t i = 0; i < endpoints_.size(); ++i) {
    names.push_back(endpoints_[i]->name());
  }
  return names;
}

void Graph::clean() {
  for (size_t i = 0; i < endpoints_.size(); ++i) {
    delete endpoints_[i];
  }
  endpoints_.clear();
}
