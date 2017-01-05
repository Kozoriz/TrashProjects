#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "tablerow.h"

class Table {
 public:
  typedef std::vector<TableRow> Rows;
  Table();
  Table(Rows initial_rows);

  Rows GetRowsWithColValue(const std::string& column,
                           const std::string& value) const;
  void Clear();
  size_t Size() const;
  const TableRow& operator[](int i) const;

  void AddRow(const TableRow& row);

  void UpdateCellValue(const int row,
                       const int column,
                       const std::string& data);

 private:
  Rows rows_;
};

#endif  // TABLE_H
