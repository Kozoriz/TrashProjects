#pragma once

#include "utils/numbers.h"

namespace engine_adapter {
/**
 * TODO need to realyze thread for adapters
 * spin methods can just set values but executing trigger via
 * cond_var.notifyall...
 */
class EngineAdapter {
 public:
  virtual void SpinForward(const utils::UInt milliseconds) const = 0;
  virtual void SpinBack(const utils::UInt milliseconds) const = 0;
};
}
