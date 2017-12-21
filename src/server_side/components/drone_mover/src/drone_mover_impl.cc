#include "drone_mover/drone_mover_impl.h"
#include "utils/logger.h"

CREATE_LOGGER("DroneMover")

namespace drone_mover {
DroneMoverImpl::DroneMoverImpl(const utils::Profile& settings)
    : settings_(settings) {
  LOG_AUTO_TRACE();
}
DroneMoverImpl::~DroneMoverImpl() {
  LOG_AUTO_TRACE();
}

utils::Vector<messages::MoveMessage*> DroneMoverImpl::MakeMoveCommadns(
    const utils::positions::Location3& drone_dislocation,
    const utils::Vector<utils::positions::Location3>& way_points) {
  LOG_AUTO_TRACE();
  // TODO
  return utils::Vector<messages::MoveMessage*>();
}
}  // namespace drone_mover
