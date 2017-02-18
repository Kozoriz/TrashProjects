#include "utils/logger.h"

#include "life_cycle.h"

CREATE_LOGGER("Main")

int main(int argc, char** argv) {
  logger::LoggerAutoPtr logger();
  LOG_AUTO_TRACE();

  LifeCycle life_cycle;
  // Components creatting
  life_cycle.InitComponents();

  // Start message listeners
  life_cycle.StartThreads();

  // Start server messages handling
  life_cycle.ListenToServer();

  // Destruct components
  life_cycle.DeinitComponents();

  return 0;
}
