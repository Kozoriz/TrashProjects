#include "databasereporter.h"
#include "logger.h"

#include <QFile>

DatabaseReporter::DatabaseReporter(const DatabaseAnalyzer& data_processor)
    : data_processor_(data_processor) {}

void DatabaseReporter::GenerateReport() const {
  GenerateTxtReport();
  GenerateDocReport();
  GeneratePdfReport();
  return;
}

void DatabaseReporter::GenerateTxtReport() const {
  QFile file("report.txt");

  std::string table_string = data_processor_.GetFilteredData().asString();

  if (!file.open(QFile::WriteOnly)) {
    LOG_MESSAGE("Can`t to open txt file");
    return;
  }

  QTextStream out(&file);
  out << "\t\tReport\n\n" << table_string.c_str() << "\t\tEND\n";

  file.flush();
  file.close();
}

void DatabaseReporter::GenerateDocReport() const {}

void DatabaseReporter::GeneratePdfReport() const {}
