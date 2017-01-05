#ifndef NUMBER_H
#define NUMBER_H

#include "primitivetype.h"

class Number : public PrimitiveType {
 public:
  Number(const std::string& initial_value);
  virtual ~Number();

  bool operator==(const std::string& other) const override;
  std::string asString() const override;

  static bool CanBeNum(const std::string& str_value);

 private:
  const float data;
};

#endif  // NUMBER_H
