#include "number.h"
#include "logger.h"

Number::Number(const std::string& initial_value)
    : data(atof(initial_value.c_str())) {
  //  LOG_MESSAGE("Number::Number::i_v=(" + initial_value + ")");
}

Number::~Number() {}

bool Number::operator==(const std::string& other) const {
  return other == asString();
}

std::string Number::asString() const {
  if (static_cast<int64_t>(data * 1000.f) % 1000 == 0) {
    return std::to_string(int64_t(data));
  }
  return std::to_string(data);
}

bool Number::CanBeNum(const std::string& str_value) {
  if (str_value.size() < 1) {
    return false;
  }
  bool dot_found = false;

  for (size_t i = 0; i < str_value.size(); ++i) {
    if (!isdigit(str_value[i])) {
      if ('.' == str_value[i]) {
        if (dot_found) {
          return false;
        }
        dot_found = true;
        continue;
      }
      return false;
    }
  }
  return true;
}
