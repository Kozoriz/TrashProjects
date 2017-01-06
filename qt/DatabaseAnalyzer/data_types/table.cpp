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

void Table::UpdateRowById(const int id, const TableRow& row) {
  const int position = FindRowPosById(id);
  if (-1 == position) {
    return;
  }
  rows_[position] = row;
}

std::string Table::asString() const {
  std::string result;
  for (size_t i = 0; i < rows_.size(); ++i) {
    result += rows_[i].asString() + "\n";
  }
  return result;
}

int Table::FindRowPosById(const int id) const {
  for (size_t i = 0; i < rows_.size(); ++i) {
    if (id == atoi(rows_[i]["id"]->asString().c_str())) {
      return i;
    }
  }
  return -1;
}
