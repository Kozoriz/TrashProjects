#include "endpoint.h"
#include "logger.h"

Endpoint::Endpoint(const std::string& name) : name_(name) {}

void Endpoint::AddNeighbor(Endpoint* neighbor, const uint32_t distance) {
  if (neighbor == this) {
    LOG_MESSAGE("Endpoint::AddNeighbor::Loop");
    return;
  }
  if (neighbors_.end() != neighbors_.find(neighbor)) {
    LOG_MESSAGE("Endpoint::AddNeighbor::Exists");
    return;
  }

  if (279 < distance) {
    LOG_MESSAGE("Endpoint::AddNeighbor::TooFaaar");
    return;
  }

  LOG_MESSAGE("Endpoint::AddNeighbor::" + this->name() + " -> " +
              neighbor->name() + " : " + std::to_string(distance));
  neighbors_.insert(NeighborDistMap::value_type(neighbor, distance));
  neighbor->AddNeighbor(this, distance);

//    if (neighbors_.size() > 4 ) {
//      RemoveHighest();
//    }
}

const Endpoint::NeighborDistMap& Endpoint::neighbors() {
  return neighbors_;
}

const std::string& Endpoint::name() {
  return name_;
}

void Endpoint::RemoveHighest() {
  Endpoint* max = NULL;
  uint32_t max_d = 0;
  for (auto& pair : neighbors_) {
    if (pair.second > max_d) {
      max = pair.first;
      max_d = pair.second;
    }
  }
  if (NULL != max) {
    RemoveNeighbor(max);
  }
}

void Endpoint::RemoveNeighbor(Endpoint* neighbor) {
  NeighborDistMap::const_iterator neighbor_it = neighbors_.find(neighbor);
  if (neighbors_.end() != neighbor_it) {
    neighbors_.erase(neighbor_it);
    neighbor->RemoveNeighbor(this);
  }
}
