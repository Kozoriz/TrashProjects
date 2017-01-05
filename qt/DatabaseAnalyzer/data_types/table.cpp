#include "table.h"

Table::Table() {}

Table::Table(Table::Rows initial_rows) : rows_(initial_rows) {}

Table::Rows Table::GetRowsWithColValue(const std::string& column,
                                       const std::string& value) const {
  Rows new_rows;
  for (const TableRow& row : rows_) {
    if (row.IsSameValueInCol(column, value)) {
      new_rows.push_back(row);
    }
  }
  return new_rows;
}

void Table::Clear() {
  rows_.clear();
}

size_t Table::Size() const {
  return rows_.size();
}

const TableRow& Table::operator[](int i) const {
  return rows_[i];
}

void Table::AddRow(const TableRow& row) {
  rows_.push_back(row);
}

void Table::UpdateCellValue(const int row,
                            const int column,
                            const std::string& data) {
  rows_[row].UpdateCellValue(column, data);
}
