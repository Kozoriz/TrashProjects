#ifndef WAY_H
#define WAY_H
#include <vector>

#include "endpoint.h"
class Way {
 public:
  Way();

  std::__cxx11::string asString() const;
  uint32_t distance() const;
  void addEndpoint(Endpoint* ep, const uint32_t distance);

 private:
  std::vector<Endpoint*> endpoints_;
  uint32_t distance_;
};

#endif  // WAY_H
