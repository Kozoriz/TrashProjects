#pragma once

#include "messages/sensor_data_message.h"
#include "snapshot_processor/snapshot.h"

namespace snapshot_processor {
class SnapshotProcessor {
 public:
  virtual const Snapshot& GetGeneratedSnapshot() const = 0;
  virtual void OnMessageReceived(
      const messages::SensorDataMessage& message) = 0;
  virtual void ClearSnapshot() = 0;
};
}
