#ifndef PRIMITIVETYPE_H
#define PRIMITIVETYPE_H

#include <string>

class PrimitiveType {
 public:
  virtual ~PrimitiveType() {}
  virtual bool operator==(const std::string& other) const = 0;
  virtual std::string asString() const = 0;
};

#endif  // PRIMITIVETYPE_H
