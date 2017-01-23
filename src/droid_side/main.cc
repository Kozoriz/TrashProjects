#include "utils/logger.h"

#include "life_cycle.h"

int main(int argc, char** argv) {
  INIT_LOGGER("logger_config.ini");
  LOG_TRACE(logger::IN);

  LifeCycle life_cycle;
  // Components creatting
  life_cycle.InitComponents();

  // Start message listeners
  life_cycle.StartThreads();

  // Start server messages handling
  life_cycle.ListenToServer();

  // Destruct components
  life_cycle.DeinitComponents();

  LOG_TRACE(logger::OUT);
  return 0;
}
