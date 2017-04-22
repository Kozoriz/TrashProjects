#include "guide/guide_impl.h"
namespace guide {
GuideImpl::GuideImpl(const utils::Profile& settings) : settings_(settings) {}
GuideImpl::~GuideImpl() {}

const utils::positions::Location3& GuideImpl::GetDroneLocation() {
  return current_dislocation_;
}
}
