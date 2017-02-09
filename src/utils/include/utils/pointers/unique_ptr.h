#pragma once

#include <memory>

namespace utils {
template<class PointerType>
class UniquePtr : public std::unique_ptr<PointerType> {};

template<class PointerType>
UniquePtr<PointerType> make_unique(Args&&... args) {
    return std::unique_ptr<PointerType>(new PointerType(std::forward<Args>(args)...));
}
}

