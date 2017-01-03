#ifndef DATABASEREPORTER_H
#define DATABASEREPORTER_H

#include "databaseanalyzer.h"

#include <string>

class DatabaseReporter {
 public:
  DatabaseReporter(const DatabaseAnalyzer& data_processor);
  std::string GenerateReport() const;

 private:
  const DatabaseAnalyzer& data_processor_;
};

#endif  // DATABASEREPORTER_H
