#ifndef DATABASEPROCESSOR_H
#define DATABASEPROCESSOR_H

#include <map>
#include <string>

#include "data_types/table.h"
#include "low_level/databasewrapper.h"

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

  DatabaseAnalyzer();
  void ImportData(const std::string& db_name);

  void FilterData(Filter filter);
  void FilterErrorData();
  const Table& GetFilteredData() const;
  const Table& GetData() const;

  void OnCellChanged(const int row, const int column, const std::string& data);

 private:
  Table table_;
  Table current_filtered_table_;

  DatabaseWrapper db_wrapper_;
};

#endif  // DATABASEPROCESSOR_H
