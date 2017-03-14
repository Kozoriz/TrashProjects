#pragma once
#include "guide/guide.h"
#include "utils/profile.h"

namespace guide {
class GuideImpl : public Guide {
 public:
  GuideImpl(const utils::Profile& settings);
  ~GuideImpl();

 private:
  const utils::Profile& settings_;
};
}
