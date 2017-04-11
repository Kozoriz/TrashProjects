#ifndef DATABASEWRAPPER_H
#define DATABASEWRAPPER_H

//#include <sqlite3.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "data_types/table.h"

typedef QSqlDatabase DatabaseType;
typedef QSqlQuery QueryType;
//typedef sqlite3 DatabaseType;

class DatabaseWrapper {
 public:
  DatabaseWrapper(Table& table);
  ~DatabaseWrapper();

  /**
   * @brief ImportData - open sql connection, read data, write data to table
   * @param database_file_name
   */
  void ImportData(const std::string& db_name);
  /**
   * @brief ExportData - open sql connection, write data from table to sql
   * database
   * @param database_file_name
   */
  void ExportData();

  DatabaseType* conn() const;

  std::string database_name_;

  std::vector<std::string> GetTableList();
private:
  bool Open();
  void Close();
  bool Exec(const std::string& query);

 private:
  Table& table_;
  std::string current_table_name;

  DatabaseType* conn_;
  int error_;

  QueryType last_query_;
};

#endif  // DATABASEWRAPPER_H
