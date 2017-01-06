#include "string.h"
#include "logger.h"

String::String(std::string initial_data) : data(initial_data) {
  //  LOG_MESSAGE("String::String::i_v=(" + initial_data + ")");
}

String::~String() {}

bool String::operator==(const std::string& other) const {
  return other == data;
}

std::string String::asString() const {
  return data;
}
