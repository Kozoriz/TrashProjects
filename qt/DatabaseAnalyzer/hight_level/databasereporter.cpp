#include "databasereporter.h"

DatabaseReporter::DatabaseReporter(const DatabaseAnalyzer& data_processor)
    : data_processor_(data_processor) {}

void DatabaseReporter::GenerateReport() const {
  GenerateTxtReport();
  GenerateDocReport();
  GeneratePdfReport();
  return;
}

void DatabaseReporter::GenerateTxtReport() {}

void DatabaseReporter::GenerateDocReport() {}

void DatabaseReporter::GeneratePdfReport() {}
