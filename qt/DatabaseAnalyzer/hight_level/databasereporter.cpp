#include "databasereporter.h"

DatabaseReporter::DatabaseReporter(const DatabaseAnalyzer& data_processor)
    : data_processor_(data_processor) {}

std::string DatabaseReporter::GenerateReport() const {
  data_processor_.GetFilteredData();
  return std::string("");
}
