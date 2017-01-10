#ifndef WAYFINDER_H
#define WAYFINDER_H

#include <map>
#include "data_types/graph.h"
#include "data_types/way.h"

class WayFinder {
 public:
  /**
 * @brief WaysMap
 * @1st key - "from" endpoint name
 * @2nd key - "to" endpoint name
 * @value - pointer to Way between endpoints
 */
  typedef std::map<std::string, std::map<std::string, Way*> > WaysMap;

  WayFinder(const Graph& graph);
  const Way* getWay(const std::string& from, const std::string& to);

  void CalculateAllWays();
  void CalculateWaysFor(const std::string& from);

  void OnGraphUpdated();
private:
  void setWay(const std::string& from, const std::string& to, Way* way);

  WaysMap ways_;
  bool ways_filled_;
  const Graph& graph_;
  void removeWay(const std::string& from, const std::string& to);
  void ProcessNeighbors(const std::string& start_ep_name,
                        Endpoint* current_ep,
                        const Way* current_way,
                        std::vector<std::string>& visited);
};

#endif  // WAYFINDER_H
