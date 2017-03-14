#pragma once
#include "snapshot_processor/snapshot_processor.h"
#include "utils/profile.h"
#include "snapshot_processor/snapshot.h"

namespace snapshot_processor {
class SnapshotProcessorImpl : public SnapshotProcessor {
 public:
  SnapshotProcessorImpl(const utils::Profile& settings);
  ~SnapshotProcessorImpl();

  const Snapshot& GetGeneratedSnapshot() const override;
  void OnMessageReceived(const messages::SensorDataMessage& message) override;
  void ClearSnapshot() override;

 private:
  const utils::Profile& settings_;

  Snapshot snapshot_;
};
}
