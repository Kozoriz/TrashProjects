#include "wayfinder.h"
#include "logger.h"

WayFinder::WayFinder(const Graph& graph) :ways_filled_(false), graph_(graph) {}

const Way* WayFinder::getWay(const std::__cxx11::string& from,
                             const std::__cxx11::string& to) {
  LOG_MESSAGE("WayFinder::getWay " + from + " --> " + to);
  WaysMap::iterator first_key_it = ways_.find(from);
  if (ways_.end() != first_key_it) {
    WaysMap::value_type::second_type& ways_from = first_key_it->second;
    WaysMap::value_type::second_type::iterator second_key_it =
        ways_from.find(to);
    if (ways_from.end() != second_key_it) {
      return second_key_it->second;
    }
  }
  LOG_MESSAGE("WayFinder::getWay::NotFound");
  return NULL;
}

void WayFinder::setWay(const std::__cxx11::string& from,
                       const std::__cxx11::string& to,
                       Way* way) {
  LOG_MESSAGE("WayFinder::setWay " + from + " --> " + to);
  WaysMap::iterator first_key_it = ways_.find(from);
  if (ways_.end() != first_key_it) {
    WaysMap::value_type::second_type& ways_from = first_key_it->second;
    WaysMap::value_type::second_type::iterator second_key_it =
        ways_from.find(to);
    if (ways_from.end() != second_key_it) {
      second_key_it->second = way;
      return;
    }
    ways_from.insert(WaysMap::value_type::second_type::value_type(to, way));
    return;
  }
  WaysMap::value_type::second_type to_map;
  to_map.insert(WaysMap::value_type::second_type::value_type(to, way));
  ways_.insert(WaysMap::value_type(from, to_map));
}

void WayFinder::CalculateAllWays() {
  LOG_MESSAGE("WayFinder::CalculateAllWays");
  if (ways_filled_) {
      LOG_MESSAGE("WayFinder::CalculateAllWays::AlreadyDone");
      return;
  }
  for (size_t i = 0; i < graph_.endpoints().size(); ++i) {
    CalculateWaysFor(graph_.endpoints()[i]->name());
  }
}

void WayFinder::CalculateWaysFor(const std::string& from) {
  LOG_MESSAGE("WayFinder::CalculateWaysFor " + from);
  std::vector<std::string> visited;
  Endpoint* start_ep = graph_.GetEndpointByName(from);
  Way* start_way = new Way();
  start_way->addEndpoint(start_ep, 0);
  setWay(from, from, start_way);

  ProcessNeighbors(from, start_ep, start_way, visited);
  ways_filled_ = true;
}

void WayFinder::ProcessNeighbors(const std::string& start_ep_name,
                                 Endpoint* current_ep,
                                 const Way* current_way,
                                 std::vector<std::string>& visited) {
  const std::string& current_name = current_ep->name();
  LOG_MESSAGE("WayFinder::ProcessNeighbors  " + current_name);
  if (visited.end() !=
      std::find(visited.begin(), visited.end(), current_name)) {
    LOG_MESSAGE("WayFinder::ProcessNeighbors::AlreadyVisited " + current_name);
    return;
  }
  visited.push_back(current_name);
  for (auto& pair : current_ep->neighbors()) {
    const std::string& neighbor_name = pair.first->name();
    const Way* neighbor_way = getWay(start_ep_name, neighbor_name);
    Way* new_way = new Way(*current_way);
    new_way->addEndpoint(pair.first, pair.second);

    if (NULL == neighbor_way) {
      LOG_MESSAGE("WayFinder::ProcessNeighbors::AddNew " + new_way->asString() +
                  "(" + std::to_string(new_way->distance()) + ")");

      setWay(start_ep_name, neighbor_name, new_way);
    } else if (neighbor_way->distance() > new_way->distance()) {
      LOG_MESSAGE("WayFinder::ProcessNeighbors::Update " + new_way->asString() +
                  "(" + std::to_string(new_way->distance()) + ")");
      removeWay(start_ep_name, neighbor_name);
      setWay(start_ep_name, neighbor_name, new_way);
    } else {
      LOG_MESSAGE("WayFinder::ProcessNeighbors::UseExisting " +
                  neighbor_way->asString() + "(" +
                  std::to_string(neighbor_way->distance()) + ")");
      delete new_way;
    }
  }
  for (auto& pair : current_ep->neighbors()) {
    ProcessNeighbors(start_ep_name, pair.first, getWay(start_ep_name, pair.first->name()), visited);
  }
}

void WayFinder::removeWay(const std::string& from, const std::string& to) {
  WaysMap::iterator first_key_it = ways_.find(from);
  if (ways_.end() != first_key_it) {
      LOG_MESSAGE("WayFinder::removeWay " + from + " --> " + to);
    WaysMap::value_type::second_type& ways_from = first_key_it->second;
    WaysMap::value_type::second_type::iterator second_key_it =
        ways_from.find(to);
    if (ways_from.end() != second_key_it) {
      LOG_MESSAGE("WayFinder::removeWay " + from + " --> " + to);
      delete second_key_it->second;
      ways_from.erase(second_key_it);
    }
  }
}

void WayFinder::OnGraphUpdated() {
    LOG_MESSAGE("WayFinder::OnGraphUpdated");
    ways_filled_ = false;
    const std::vector<std::string>& names = graph_.EndpointsNames();
    for (size_t i = 0; i < names.size(); ++i) {
        for (size_t j = 0; j < names.size(); ++j) {
            removeWay(names[i], names[j]);
        }
    }
    LOG_MESSAGE("WayFinder::OnGraphUpdated::Clear");
}
