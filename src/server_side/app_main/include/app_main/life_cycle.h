#pragma once

#include "drone_message_handler/drone_message_handler.h"
#include "snapshot_processor/snapshot_processor.h"
#include "map_assembler/map_assembler.h"
#include "map_detalization_analyzer/map_detalization_analyzer.h"
#include "guide/guide.h"
#include "drone_mover/drone_mover.h"

#include "utils/threads/thread.h"
#include "utils/pointers/unique_ptr.h"

#include "utils/profile.h"
#include "app_main/message_listener.h"

class LifeCycle : public MessageListener {
 public:
  void InitComponents();
  void DeinitComponents();
  void StartThreads();
  int ListenToClient();

  void OnDataMessageReceived(
      const messages::SensorDataMessage& message) override;
  void OnFinalMessageReceived() override;

 private:
  utils::Profile* settings_;

  drone_message_handler::DroneMessageHandler* message_handler_;
  snapshot_processor::SnapshotProcessor* snapshot_processor_;
  map_assembler::MapAssembler* map_assembler_;
  map_detalization_analyzer::MapDetalizationAnalyzer*
      map_detalization_analyzer_;
  guide::Guide* guide_;
  drone_mover::DroneMover* drone_mover_;
};
