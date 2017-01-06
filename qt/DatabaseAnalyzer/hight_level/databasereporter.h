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
  void GenerateTxtReport() const;
  void GenerateDocReport() const;
  void GeneratePdfReport() const;
};

#endif  // DATABASEREPORTER_H
