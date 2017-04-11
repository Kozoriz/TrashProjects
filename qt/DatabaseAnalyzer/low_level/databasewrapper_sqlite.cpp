#include "databasewrapper.h"
#include "logger.h"
#include "low_level/sql_query.h"

namespace queries {
const std::string kSelectAllData = "SELECT * from storage";
const std::string kSelectAllColumns = "PRAGMA table_info(storage)";
const std::string kUpdateTable = "UPDATE `storage` SET ";

std::string GenerateUpdateRowQuery(const TableRow& row) {
  std::string query = kUpdateTable;
  const std::vector<std::string> keys = row.Keys();
  for (size_t i = 0; i < keys.size(); ++i) {
    if ("id" != keys[i]) {
      query += "'" + keys[i] + "' = '" + row[keys[i]]->asString() + "', ";
    }
  }
  query.erase(query.find_last_of(','));
  query += " WHERE id = " + std::to_string(atoi(row["id"]->asString().c_str()));
  return query;
}
}

DatabaseWrapper::DatabaseWrapper(Table& table) : table_(table), conn_(NULL) {
  LOG_MESSAGE("DatabaseWrapper::DatabaseWrapper");
}

void DatabaseWrapper::ImportData(const std::string& db_name) {
  LOG_MESSAGE("DatabaseWrapper::ImportData");
  database_name_ = db_name;
  table_.Clear();

  if (Open()) {
    LOG_MESSAGE("DatabaseWrapper::ImportData::DB_Opened");

    SQLQuery columns_query(*this);
    if (!columns_query.Prepare(queries::kSelectAllColumns)) {
      LOG_MESSAGE("Prepare error : " + columns_query.LastError());
    }

    LOG_MESSAGE("DatabaseWrapper::GettingTableSchema");
    std::vector<std::string> columns;
    while (columns_query.Next()) {
      std::string col = columns_query.GetString(1);
      columns.push_back(col);
      LOG_MESSAGE("Col : " + col);
    }

    LOG_MESSAGE("Columns size : " + std::to_string(columns.size()));

    SQLQuery query(*this);
    if (!query.Prepare(queries::kSelectAllData)) {
      LOG_MESSAGE("Prepare error : " + query.LastError());
    }
    while (query.Next()) {
      TableRow row;
      for (size_t i = 0; i < columns.size(); ++i) {
        row.InsertCellValue(columns[i], query.GetString(i));
      }
      table_.AddRow(row);
    }

    Close();
  }
}

void DatabaseWrapper::ExportData() {
  if (Open()) {
    for (size_t i = 0; i < table_.Size(); ++i) {
      const std::string query = queries::GenerateUpdateRowQuery(table_[i]);
      LOG_MESSAGE("DatabaseWrapper::ExportData::" + query);
      if (!Exec(query)) {
        LOG_MESSAGE("DatabaseWrapper::ExecError" + std::to_string(error_));
        Close();
        return;
      }
    }
    LOG_MESSAGE("DatabaseWrapper::Export::Complete");
    Close();
  }
}

sqlite3* DatabaseWrapper::conn() const {
  return conn_;
}

bool DatabaseWrapper::Open() {
  LOG_MESSAGE("DatabaseWrapper::Open");
  if (conn_) {
    return true;
  }
  error_ = sqlite3_open(database_name_.c_str(), &conn_);
  return error_ == SQLITE_OK;
}

void DatabaseWrapper::Close() {
  LOG_MESSAGE("DatabaseWrapper::Close");
  if (!conn_) {
    return;
  }

  error_ = sqlite3_close(conn_);
  if (error_ == SQLITE_OK) {
    conn_ = NULL;
  }
}

bool DatabaseWrapper::Exec(const std::string& query) {
  error_ = sqlite3_exec(conn_, query.c_str(), NULL, NULL, NULL);
  return error_ == SQLITE_OK;
}
