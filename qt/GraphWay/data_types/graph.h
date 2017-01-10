#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "endpoint.h"

class Graph {
 public:
  Graph();
  ~Graph();
  void AddEndpoint(Endpoint* ep);
  const std::vector<Endpoint*>& endpoints() const;
  Endpoint* GetEndpointByName(const std::string& name) const;

  std::vector<std::string> EndpointsNames() const;
  void clean();

 private:
  std::vector<Endpoint*> endpoints_;
};

#endif  // GRAPH_H
