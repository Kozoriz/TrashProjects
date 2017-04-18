#include "utils/structures/matrix3.h"
#include "utils/containers/string.h"

namespace utils {
namespace structures {

size_t Hash::operator()(const positions::Location3 &pos) const
{
    Stringstream ss;
    ss << "[" << pos.x_ << ", " << pos.y_ << ", " << pos.z_ << "]";
    String value = ss.str();
    return HashFunc<String>()(value);
}

bool Matrix3::IsExists(const positions::Location3 &pos) const
{
    return storage_.end() != storage_.find(pos);
}

bool Matrix3::IsExists(const UInt x, const UInt y, const UInt z) const
{
  positions::Location3 pos;
  pos.x_ = x;
  pos.y_ = y;
  pos.z_ = z;
  return IsExists(pos);
}

void Matrix3::AddPoint(const positions::Location3 &pos)
{
  storage_.insert(pos);
}

void Matrix3::AddPoint(const UInt x, const UInt y, const UInt z)
{
  positions::Location3 pos;
  pos.x_ = x;
  pos.y_ = y;
  pos.z_ = z;
  AddPoint(pos);
}

void Matrix3::RemovePoint(const positions::Location3 &pos)
{
  storage_.erase(pos);
}

void Matrix3::RemovePoint(const UInt x, const UInt y, const UInt z)
{
  positions::Location3 pos;
  pos.x_ = x;
  pos.y_ = y;
  pos.z_ = z;
  RemovePoint(pos);
}

Matrix3 &Matrix3::operator+=(const Matrix3 &another_matrix)
{
  storage_.insert(another_matrix.storage_.begin(), another_matrix.storage_.end());
}

UInt Matrix3::Size() const
{
  return storage_.size();
}



}  // namespace structures
}  // namepsace utils
