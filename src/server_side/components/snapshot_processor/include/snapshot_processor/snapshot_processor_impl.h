#pragma once
#include "snapshot_processor/snapshot_processor.h"
#include "utils/profile.h"

namespace snapshot_processor {
class SnapshotProcessorImpl : public SnapshotProcessor {
 public:
  SnapshotProcessorImpl(const utils::Profile& settings);
  ~SnapshotProcessorImpl();

  SnapshotSPtr GetGeneratedSnapshot() const override;
  void OnMessageReceived(const messages::SensorDataMessage& message) override;
  void ClearSnapshot() override;
  void SaveSnapshotFile() const override;

 private:
  const utils::Profile& settings_;

  SnapshotSPtr snapshot_;
};
}
