#pragma once

#include "engine_adapter/engine_adapter.h"
namespace engine_adapter {

class EngineAdapterImpl : public EngineAdapter {
 public:
  void SpinForward(const utils::UInt milliseconds) const override;
  void SpinBack(const utils::UInt milliseconds) const override;
};
}
