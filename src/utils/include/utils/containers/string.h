#pragma once

#include <sstream>
#include <string>

namespace utils {
/**
 * @brief String - TODO implement own string
 */
typedef std::string String;
typedef std::stringstream Stringstream;

template <typename Type>
utils::String ConvertToString(Type value) {
  return static_cast<std::ostringstream*>(&(std::ostringstream() << value))
      ->str();
}
}
