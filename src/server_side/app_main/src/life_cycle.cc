#include "app_main/life_cycle.h"

#include "utils/logger.h"
#include "utils/containers/string.h"
#include "utils/profile_impl.h"

#include "drone_message_handler/drone_message_handler_impl.h"
#include "snapshot_processor/snapshot_processor_impl.h"
#include "map_assembler/map_assembler_impl.h"
#include "map_detalization_analyzer/map_detalization_analyzer_impl.h"
#include "guide/guide_impl.h"
#include "drone_mover/drone_mover_impl.h"

CREATE_LOGGER("Main")
#include <stdlib.h>

#include "messages/move_message.h"

void LifeCycle::InitComponents() {
  LOG_AUTO_TRACE();

  const utils::String file_name = "enviroment_scanner_server.ini";
  settings_ = new utils::ProfileImpl(file_name);
  drone_mover_ = new drone_mover::DroneMoverImpl(*settings_);
  guide_ = new guide::GuideImpl(*settings_);
  map_detalization_analyzer_ =
      new map_detalization_analyzer::MapDetalizationAnalyzerImpl(*settings_);
  map_assembler_ = new map_assembler::MapAssemblerImpl(*settings_);
  snapshot_processor_ =
      new snapshot_processor::SnapshotProcessorImpl(*settings_);

  message_handler_ =
      new drone_message_handler::DroneMessageHandlerImpl(*settings_, *this);
}

void LifeCycle::DeinitComponents() {
  LOG_AUTO_TRACE();
  delete snapshot_processor_;
  delete map_assembler_;
  delete guide_;
  delete drone_mover_;

  delete message_handler_;

  delete settings_;
}

void LifeCycle::StartThreads() {
  LOG_AUTO_TRACE();
}

int LifeCycle::ListenToClient() {
  LOG_AUTO_TRACE();
  message_handler_->SendMessageToDroid(new messages::Message(
      messages::MessageType::START_SCAN));
  message_handler_->Run();
}

void LifeCycle::OnDataMessageReceived(
    const messages::SensorDataMessage& message) {
  LOG_AUTO_TRACE();
  snapshot_processor_->OnMessageReceived(message);
}

void LifeCycle::OnFinalMessageReceived() {
  LOG_AUTO_TRACE();
  LOG_DEBUG("Getting snapshot.");

  utils::SharedPtr<snapshot_processor::Snapshot> snapshot =
      snapshot_processor_->GetGeneratedSnapshot();
  snapshot_processor_->SaveSnapshotFile();

  const utils::positions::Location3& drone_dislocation =
      guide_->GetDroneLocation();

  map_assembler_->AttachSnapshotToMap(snapshot, drone_dislocation);
  const map_assembler::Map& actual_map = map_assembler_->GetActualMap();
  map_assembler_->SaveMapFile();

  map_detalization_analyzer::PointsArray possible_analisation_points =
      map_detalization_analyzer_->ProcessAnalisationPoints(actual_map);

  guide::PointsArray way_points =
      guide_->GetWayPointsToNearestLocation(possible_analisation_points);

  utils::Vector<messages::MoveMessage*> move_messages =
      drone_mover_->MakeMoveCommadns(drone_dislocation, way_points);

  for (auto message : move_messages) {
    message_handler_->SendMessageToDroid(message);
  }

//  message_handler_->SendMessageToDroid(
//      new messages::Message(messages::MessageType::START_SCAN));

  // Clear snapshot in the end
  snapshot_processor_->ClearSnapshot();
}
