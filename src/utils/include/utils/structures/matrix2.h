#pragma once

#include "utils/containers/vector.h"
#include "utils/structures/position.h"
#include "utils/macro.h"

namespace utils {
namespace structures {
/**
 * @brief The Matrix2 - saves values of x,y coordinates in horizontal projection
 */
template <typename ValueType>
class Matrix2 {
 public:
  typedef Vector<ValueType> YConteinerType;
  typedef Vector<YConteinerType> ContainerType;
  Matrix2();
  Matrix2(const utils::UInt x_size, const utils::UInt y_size);

  const YConteinerType& operator[](const utils::UInt x_position);
  void SetValue(const utils::UInt x_pos,
                const utils::UInt y_pos,
                const ValueType& value);

  Matrix2<ValueType>& operator+=(const Matrix2<ValueType>& another_matrix);

  utils::UInt XSize() const;

 private:
  ContainerType storage_;
};



template <typename ValueType>
Matrix2<ValueType>::Matrix2() {}

template <typename ValueType>
Matrix2<ValueType>::Matrix2(const utils::UInt x_size,
                            const utils::UInt y_size) {
  storage_.resize(x_size);
  for (auto y_storage : storage_) {
    y_storage.resize(y_size);
  }
}

template <typename ValueType>
const typename Matrix2<ValueType>::YConteinerType& Matrix2<ValueType>::
operator[](const utils::UInt x_position) {
  DCHECK(x_position < storage_.size());
  return storage_[x_position];
}

template <typename ValueType>
void Matrix2<ValueType>::SetValue(const utils::UInt x_pos,
                                  const utils::UInt y_pos,
                                  const ValueType& value) {
  if (x_pos >= storage_.size()) {
    storage_.resize(x_pos + 1);
  }
  if (y_pos >= storage_[x_pos].size()) {
    storage_[x_pos].resize(y_pos + 1);
  }
  storage_[x_pos][y_pos] = value;
}

template <typename ValueType>
Matrix2<ValueType>& Matrix2<ValueType>::operator+=(
    const Matrix2<ValueType>& another_matrix) {
  const utils::UInt x_size = another_matrix.XSize();
  for (utils::UInt x = 0; x < x_size; ++x) {
    const utils::UInt y_size = another_matrix[x].size();
    for (utils::UInt y = 0; y < y_size; ++y) {
      SetValue(x, y, another_matrix[x][y]);
    }
  }
}

template <typename ValueType>
utils::UInt Matrix2<ValueType>::XSize() const {
  return storage_.size();
}

}  // namespace structures
}  // namespace utils
