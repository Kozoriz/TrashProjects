#include "databaseanalyzer.h"

DatabaseAnalyzer::DatabaseAnalyzer(const std::string& database_file_name)
    : database_file_name_(database_file_name)
    , table_()
    , current_filtered_table_()
    , db_wrapper_(table_) {
  db_wrapper_.ImportData(database_file_name_);
}

void DatabaseAnalyzer::FilterData(DatabaseAnalyzer::Filter filter) {}

const Table& DatabaseAnalyzer::GetFilteredData() const {
  return current_filtered_table_;
}
