#ifndef STRING_H
#define STRING_H

#include "primitivetype.h"

class String : public PrimitiveType {
 public:
  String(std::string initial_data);
  virtual ~String();

  bool operator==(const std::string& other) const override;
  std::string asString() const override;

 public:
  const std::string data;
};

#endif  // STRING_H
