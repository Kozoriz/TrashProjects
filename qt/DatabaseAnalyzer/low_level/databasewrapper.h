#ifndef DATABASEWRAPPER_H
#define DATABASEWRAPPER_H

#include <sqlite3.h>

#include "data_types/table.h"

class DatabaseWrapper {
 public:
  DatabaseWrapper(Table& table);

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

  sqlite3* conn() const;

  std::string database_name_;

 private:
  bool Open();
  void Close();
  bool Exec(const std::string& query);

 private:
  Table& table_;

  sqlite3* conn_;
  int error_;
};

#endif  // DATABASEWRAPPER_H
