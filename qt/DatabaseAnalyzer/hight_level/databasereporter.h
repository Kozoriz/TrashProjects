#ifndef DATABASEREPORTER_H
#define DATABASEREPORTER_H

#include "databaseanalyzer.h"

#include <string>

class DatabaseReporter {
 public:
  DatabaseReporter(const DatabaseAnalyzer& data_processor);
  void GenerateReport() const;

 private:
  const DatabaseAnalyzer& data_processor_;
  void GenerateTxtReport();
  void GenerateDocReport();
  void GeneratePdfReport();
};

#endif  // DATABASEREPORTER_H
