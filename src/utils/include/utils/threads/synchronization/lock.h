#pragma once

#include <mutex>
#include "utils/macro.h"

namespace utils {
namespace synchronization {
class Lock {
 public:
  Lock();
  void Acquire();
  void Release();
  void Try();

private:
  std::unique_lock<std::mutex> std_unique_lock_;
  friend class ConditionalVariable;
  DISALLOW_COPY_AND_ASSIGN(Lock)
};
}
}
