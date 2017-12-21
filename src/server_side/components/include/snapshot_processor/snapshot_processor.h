#pragma once

#include "messages/sensor_data_message.h"
#include "snapshot_processor/snapshot.h"
#include "utils/pointers/shared_prt.h"

namespace snapshot_processor {
class SnapshotProcessor {
 public:
  virtual SnapshotSPtr GetGeneratedSnapshot() const = 0;
  virtual void OnMessageReceived(
      const messages::SensorDataMessage& message) = 0;
  virtual void ClearSnapshot() = 0;
  virtual void SaveSnapshotFile() const = 0;
};
}
