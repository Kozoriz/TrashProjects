#ifndef DATABASEWRAPPER_H
#define DATABASEWRAPPER_H

#include "table.h"

class DatabaseWrapper {
 public:
  DatabaseWrapper(Table& table);

  /**
   * @brief ImportData - open sql connection, read data, write data to table
   * @param database_file_name
   */
  void ImportData(std::string database_file_name);
  /**
   * @brief ExportData - open sql connection, write data from table to sql
   * database
   * @param database_file_name
   */
  void ExportData(std::string database_file_name);

 private:
  Table& table_;
};

#endif  // DATABASEWRAPPER_H
