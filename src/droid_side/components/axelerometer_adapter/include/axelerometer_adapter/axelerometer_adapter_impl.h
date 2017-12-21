#pragma once

#include "axelerometer_adapter/axelerometer_adapter.h"

namespace axelerometer_adapter {

class AxelerometerAdapterImpl : public AxelerometerAdapter {
 public:
  virtual utils::positions::Incline GetData() const override;
};
}
