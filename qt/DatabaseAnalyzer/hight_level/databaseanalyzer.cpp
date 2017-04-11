#include "databaseanalyzer.h"

#include "logger.h"

namespace {
Table::Rows& operator+=(Table::Rows& a, const Table::Rows& b) {
  for (size_t i = 0; i < b.size(); ++i) {
    a.push_back(b[i]);
  }
  return a;
}
}

DatabaseAnalyzer::DatabaseAnalyzer()
    : table_(), current_filtered_table_(), db_wrapper_(table_) {
  LOG_MESSAGE("DatabaseAnalyzer::DatabaseAnalyzer");
  ProcessTableList();
}

void DatabaseAnalyzer::ProcessTableList() {
    LOG_MESSAGE("DatabaseAnalyzer::ProcessTableLis");
    tables_list_ = db_wrapper_.GetTableList();
}
const std::vector<std::string>& DatabaseAnalyzer::GetTableList() const {
    LOG_MESSAGE("DatabaseAnalyzer::GetTableList");
    return tables_list_;
}


void DatabaseAnalyzer::ImportData(const std::string& db_name) {
  db_wrapper_.ImportData(db_name);
  current_filtered_table_ = table_;
}

void DatabaseAnalyzer::ExportData() {
  db_wrapper_.ExportData();
}

void DatabaseAnalyzer::FilterData(Filter filter) {
  LOG_MESSAGE("DatabaseAnalyzer::FilterData");
  current_filtered_table_.Clear();
  current_filtered_table_ = table_;

  for (auto& it : filter) {
    LOG_MESSAGE("DatabaseAnalyzer::FilterData::filtering : (" + it.first +
                " : " + it.second + ")");
    current_filtered_table_ =
        Table(current_filtered_table_.GetRowsWithColValue(it.first, it.second));
  }
}

void DatabaseAnalyzer::OnCellChanged(const int row,
                                     const int column,
                                     const std::string& data) {
  TableRow changed_row = current_filtered_table_[row];
  const int id = atoi(changed_row["id"]->asString().c_str());

  changed_row.UpdateCellValue(column, data);

  current_filtered_table_.UpdateRowById(id, changed_row);
  table_.UpdateRowById(id, changed_row);
}

void DatabaseAnalyzer::FilterErrorData() {
  LOG_MESSAGE("DatabaseAnalyzer::FilterErrorData");
  current_filtered_table_.Clear();

  std::vector<std::string> keys = table_[0].Keys();
  Table::Rows filtered_rows;
  for (size_t i = 0; i < keys.size(); ++i) {
    filtered_rows += table_.GetRowsWithColValue(keys[i], "");
  }
  current_filtered_table_ = Table(filtered_rows);
}

const Table& DatabaseAnalyzer::GetFilteredData() const {
  LOG_MESSAGE("DatabaseAnalyzer::GetFilteredData");
  return current_filtered_table_;
}

const Table& DatabaseAnalyzer::GetData() const {
  LOG_MESSAGE("DatabaseAnalyzer::GetData");
  return table_;
}
