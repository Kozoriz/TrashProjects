#ifndef TABLEROW_H
#define TABLEROW_H

#include <map>
#include <string>
#include <vector>

#include "data_types/primitivetype.h"

class TableRow {
 public:
  TableRow();
  bool IsSameValueInCol(const std::string& col, const std::string& value) const;
  void InsertCellValue(const std::string& col, const std::string& value);
  const PrimitiveType* operator[](const std::string& key) const;
  std::vector<std::string> Keys() const;

  void UpdateCellValue(const int column, const std::string& new_data);
  std::string asString() const;

 private:
  typedef std::map<std::string, PrimitiveType*> RowData;
  RowData data_;
};

#endif  // TABLEROW_H
