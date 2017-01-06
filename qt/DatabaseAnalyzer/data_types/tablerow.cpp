#include "data_types/tablerow.h"
#include "data_types/number.h"
#include "data_types/string.h"

TableRow::TableRow() {}

bool TableRow::IsSameValueInCol(const std::string& col,
                                const std::string& value) const {
  const PrimitiveType* col_data = data_.find(col)->second;
  return *col_data == value;
}

void TableRow::InsertCellValue(const std::string& col,
                               const std::string& value) {
  PrimitiveType* data = NULL;
  if (Number::CanBeNum(value)) {
    data = new Number(value);
  } else {
    data = new String(value);
  }
  TableRow::RowData::value_type pair(col, data);
  data_.insert(pair);
}

const PrimitiveType* TableRow::operator[](const std::string& key) const {
  return data_.find(key)->second;
}

std::vector<std::string> TableRow::Keys() const {
  std::vector<std::string> keys;
  for (auto& pair : data_) {
    keys.push_back(pair.first);
  }
  return keys;
}

void TableRow::UpdateCellValue(const int column, const std::string& new_data) {
  const std::string key = Keys()[column];
  RowData::iterator it = data_.find(key);

  PrimitiveType* data = NULL;
  if (Number::CanBeNum(new_data)) {
    data = new Number(new_data);
  } else {
    data = new String(new_data);
  }
  it->second = data;
}

std::string TableRow::asString() const {
  std::string result = "|";
  std::vector<std::string> keys = Keys();
  for (size_t i = 0; i < keys.size(); ++i) {
    result += "| " + data_.find(keys[i])->second->asString() + " ";
  }
  result += "||";
  return result;
}
