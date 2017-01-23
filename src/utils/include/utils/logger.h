#pragma once

#pragma once

//#include "../../3rd_party/logger/easylogging++.h"

// INITIALIZE_EASYLOGGINGPP

#include <iostream>
#define LOG(LEVEL) std::cout

namespace logger {
enum { IN, OUT };
}

#define INIT_LOGGER(file_name) /*      \
   el::Configurations conf(file_name); \
   el::Loggers::reconfigureAllLoggers(conf);*/

#define LOG_TRACE(state)     \
  if (logger::IN == state) { \
    LOG(TRACE) << "Enter";   \
  } else {                   \
    LOG(TRACE) << "Exit";    \
  }

#define LOG_DEBUG(message) LOG(DEBUG) << message;

#define LOG_ERROR(message) LOG(ERROR) << message;

#define LOG_INFO(message) LOG(INFO) << message;
