#pragma once

#include <memory>

namespace utils {
template <class PointerType>
using SharedPtr = std::shared_ptr<PointerType>;

template <class PointerType>
SharedPtr<PointerType> make_shared(Args&&... args) {
  return std::make_shared<PointerType>(args);
}
}
