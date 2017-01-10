#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <stdint.h>
#include <map>

class Endpoint {
 public:
  typedef std::map<Endpoint*, uint32_t> NeighborDistMap;
  Endpoint(const std::string& name);

  void AddNeighbor(Endpoint* neighbor, const uint32_t distance);

  const NeighborDistMap& neighbors();
  const std::string& name();

 private:
  NeighborDistMap neighbors_;
  const std::string name_;
  void RemoveHighest();
  void RemoveNeighbor(Endpoint* neighbor);
};

#endif  // ENDPOINT_H
