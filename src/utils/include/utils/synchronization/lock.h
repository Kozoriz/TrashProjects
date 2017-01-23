#pragma once

namespace utils {
namespace synchronization {
class Lock {
 public:
  void Acquire();
  void Release();
};
}
}
