#ifndef DATABASEPROCESSOR_H
#define DATABASEPROCESSOR_H

#include <map>
#include <string>

#include "databasewrapper.h"
#include "table.h"

class DatabaseAnalyzer {
 public:
  /**
   * @brief Filter - datatype for filtering
   * from table_ to current_filtered_table_
   *
   * @keyword - table column name
   * @value - value, which will be converted to correct type
   * and used for choosing result rows
   */
  typedef std::map<std::string, std::string> Filter;

  DatabaseAnalyzer(const std::string& database_file_name);
  void FilterData(Filter filter);
  const Table &GetFilteredData() const;

 private:
  const std::string database_file_name_;

  Table table_;
  Table current_filtered_table_;

  const DatabaseWrapper db_wrapper_;
};

#endif  // DATABASEPROCESSOR_H
