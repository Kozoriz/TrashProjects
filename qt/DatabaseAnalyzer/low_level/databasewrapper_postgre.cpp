#include "databasewrapper.h"
#include "logger.h"
#include "low_level/sql_query.h"

#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlResult>

namespace queries {
const std::string kSelectAllData = "SELECT * FROM %1";
//const std::string kSelectAllColumns = "PRAGMA table_info(%1)";
const std::string kSelectAllColumns = "SELECT column_name FROM information_schema.columns WHERE table_name='%1'";
const std::string kUpdateTable = "UPDATE %1 SET ";

//const std::string kGetTableList = "SELECT table_schema,table_name FROM information_schema.tables ORDER BY table_schema,table_name";
const std::string kGetTableList = "SELECT * FROM pg_catalog.pg_tables";

const std::string kBeginTransaction = "BEGIN TRANSACTION";
const std::string kEndTransaction = "END TRANSACTION";

std::string GenerateUpdateRowQuery(const std::string& table, const TableRow& row) {
  std::string query = QString(kUpdateTable.c_str()).arg(table.c_str()).toStdString();
  const std::vector<std::string> keys = row.Keys();
  for (size_t i = 0; i < keys.size(); ++i) {
    if ("id" != keys[i]) {
      query += keys[i] + " = '" + row[keys[i]]->asString() + "', ";
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

DatabaseWrapper::~DatabaseWrapper() {
  Close();
}

void DatabaseWrapper::ImportData(const std::string& table_name) {
  LOG_MESSAGE("DatabaseWrapper::ImportData");
  current_table_name = table_name;
  table_.Clear();

  if (Open()) {
    LOG_MESSAGE("DatabaseWrapper::ImportData::DB_Opened");

    QString get_all_columns_query_string = QString(queries::kSelectAllColumns.c_str()).arg(table_name.c_str());
    Exec(queries::kBeginTransaction);
    Exec(get_all_columns_query_string.toStdString());

    LOG_MESSAGE("DatabaseWrapper::GettingTableSchema");
    std::vector<std::string> columns;
    while (last_query_.next()) {
      std::string col = last_query_.value(0).toString().toStdString();
      columns.push_back(col);
      LOG_MESSAGE("Col : " + col);
    }
    Exec(queries::kEndTransaction);

    LOG_MESSAGE("Columns size : " + std::to_string(columns.size()));

    QString get_all_data_query_string = QString(queries::kSelectAllData.c_str()).arg(table_name.c_str());
    Exec(queries::kBeginTransaction);
    Exec(get_all_data_query_string.toStdString());

    while (last_query_.next()) {
      TableRow row;
      for (size_t i = 0; i < columns.size(); ++i) {
        const std::string value = last_query_.value(i).toString().toStdString();
        row.InsertCellValue(columns[i], value);
        LOG_MESSAGE("Read value : " + value);
      }
      table_.AddRow(row);
    }
    Exec(queries::kEndTransaction);
  }
}

void DatabaseWrapper::ExportData() {
  if (Open()) {
    Exec(queries::kBeginTransaction);
    for (size_t i = 0; i < table_.Size(); ++i) {
      const std::string query = queries::GenerateUpdateRowQuery(current_table_name, table_[i]);
      LOG_MESSAGE("DatabaseWrapper::ExportData::" + query);
      if (!Exec(query)) {
        LOG_MESSAGE("DatabaseWrapper::ExecError" + std::to_string(error_));
        Close();
        return;
      }
    }
    LOG_MESSAGE("DatabaseWrapper::Export::Complete");
    Exec(queries::kEndTransaction);
  }
}

DatabaseType* DatabaseWrapper::conn() const {
  return conn_;
}

bool DatabaseWrapper::Open() {
  if (conn_ && conn_->isOpen()) return true;
  LOG_MESSAGE("DatabaseWrapper::Open");
  conn_ = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
  conn_->setHostName("localhost");
  conn_->setDatabaseName("accountant_db");
  conn_->setUserName("andrii");
  conn_->setPassword("123456");
  bool connectioncheck = conn_->open();
  if (connectioncheck == true){
       LOG_MESSAGE("Connection to database established.");
  } else {
       LOG_MESSAGE("Error for database " + conn_->databaseName().toStdString() + " : " + conn_->lastError().text().toStdString());
  }
  return connectioncheck;
}

void DatabaseWrapper::Close() {
  LOG_MESSAGE("DatabaseWrapper::Close");
  conn_->close();
  delete conn_;
  conn_ = NULL;
}

bool DatabaseWrapper::Exec(const std::string& query) {
  LOG_MESSAGE("DB wrapper exec : " + query);
  if (last_query_.isActive()) {
    last_query_.finish();
  }
  last_query_ = conn_->exec(query.c_str());
  return true;
}

std::vector<std::string> DatabaseWrapper::GetTableList() {
    LOG_MESSAGE("DatabaseWrapper::GetTableList");
    std::vector<std::string> array_;
    if (Open()) {
        LOG_MESSAGE("DatabaseWrapper::GetTableList::DB_OPENED");
        Exec(queries::kGetTableList);
        LOG_MESSAGE("DatabaseWrapper::GetTableList::DB_exec");
        while(last_query_.next()) {
            array_.push_back(last_query_.value(1).toString().toStdString());
        }
        Close();
    } else {
        LOG_MESSAGE("ERROR : database not opened!!");
    }
    LOG_MESSAGE("DatabaseWrapper::GetTableList::EXIT");
    return array_;
}
