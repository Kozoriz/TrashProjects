#pragma once

#include "utils/structures/position.h"
#include "utils/threads/thread_runnable.h"

namespace scanner {
class Scanner : public utils::threads::ThreadRunnable {
 public:
  virtual void OnScanningTriggered() = 0;
};
}
