#pragma once

#include "utils/numbers.h"
#include "utils/structures/matrix2.h"
#include "utils/macro.h"

namespace utils {
namespace structures {

template <typename ValueType>
class Matrix3 {
 public:
  // In case 3D matrix Matric2 will save Y and Z values
  typedef Matrix2<ValueType> YZConteinerType;
  typedef Vector<YZConteinerType> ConteinerType;

  Matrix3();
  Matrix3(const utils::UInt x_size,
          const utils::UInt y_size,
          const utils::UInt z_size);

  const YZConteinerType& operator[](const utils::UInt x_position) const;
  void SetValue(const utils::UInt x_pos,
                const utils::UInt y_pos,
                const utils::UInt z_pos,
                const ValueType& value);

  Matrix3<ValueType>& operator+=(const Matrix3<ValueType>& another_matrix);

  utils::UInt XSize() const;

 private:
  ConteinerType storage_;
};

template <typename ValueType>
Matrix3<ValueType>::Matrix3() {}

template<typename ValueType>
Matrix3<ValueType>::Matrix3(const utils::UInt x_size,
                            const utils::UInt y_size,
                            const utils::UInt z_size) {
  storage_.resize(x_size);
  for (auto& matrix2 : storage_) {
    matrix2.SetValue(y_size - 1, z_size - 1, ValueType());
  }
}

template <typename ValueType>
const typename Matrix3<ValueType>::YZConteinerType& Matrix3<ValueType>::
operator[](const utils::UInt x_position) const {
  DCHECK(x_position < storage_.size());
  return storage_[x_position];
}

template <typename ValueType>
void Matrix3<ValueType>::SetValue(const utils::UInt x_pos,
                                  const utils::UInt y_pos,
                                  const utils::UInt z_pos,
                                  const ValueType& value) {
  if (x_pos >= storage_.size()) {
    storage_.resize(x_pos + 1);
  }
  storage_[x_pos].SetValue(y_pos,z_pos,value);
}

template <typename ValueType>
Matrix3<ValueType>& Matrix3<ValueType>::operator+=(
    const Matrix3<ValueType>& another_matrix) {
  const utils::UInt x_size = another_matrix.XSize();
  for (utils::UInt x = 0; x < x_size; ++x) {
    storage_[x] += another_matrix[x];
  }
}

template <typename ValueType>
utils::UInt Matrix3<ValueType>::XSize() const {
  return storage_.size();
}

}  // namepace structures
}  // namespace utils
