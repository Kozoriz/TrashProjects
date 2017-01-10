#include "way.h"

Way::Way() : distance_(0) {}

std::string Way::asString() const {
  if (0 == endpoints_.size()) {
    return "Way to void!";
  }
  std::string way_string;
  for (size_t i = 0; i < endpoints_.size(); ++i) {
    way_string += endpoints_[i]->name() + "-->";
  }
  way_string.erase(way_string.find_last_of('-') - 1);
  return way_string;
}

uint32_t Way::distance() const {
  return distance_;
}

void Way::addEndpoint(Endpoint* ep, const uint32_t distance) {
  endpoints_.push_back(ep);
  distance_ += distance;
}
