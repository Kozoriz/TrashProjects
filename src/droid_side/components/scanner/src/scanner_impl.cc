#include "scanner/scanner_impl.h"
#include "server_message_handler/server_message_handler.h"

#include "utils/threads/synchronization/auto_lock.h"

#include "utils/logger.h"

CREATE_LOGGER("Scanner")

namespace {
utils::positions::Incline operator+(const utils::positions::Incline& a,
                                    const utils::positions::Incline& b) {
  utils::positions::Incline result;
  result.alpha_ = a.alpha_ + b.alpha_;
  result.beta_ = a.beta_ + b.beta_;
  return result;
}

const utils::UInt default_waiting_timeout = 100u;
}

scanner::ScannerImpl::ScannerImpl(
    const sensor_adapter::SensorAdapter& sensor_adapter,
    servo_adapter::ServoAdapter& x_servo_adapter,
    servo_adapter::ServoAdapter& y_servo_adapter,
    const axelerometer_adapter::AxelerometerAdapter& axelerometer_adapter,
    const utils::Profile& settings)
    : sensor_(sensor_adapter)
    , x_rotator_(x_servo_adapter)
    , y_rotator_(y_servo_adapter)
    , axelerometer_adapter_(axelerometer_adapter)
    , is_scanning_allowed_(false)
    , finalyzing_(false)
    , settings_(settings) {
  LOG_AUTO_TRACE();
}

scanner::ScannerImpl::~ScannerImpl() {
  LOG_AUTO_TRACE();
  Join();
}

void scanner::ScannerImpl::OnScanningTriggered() {
  LOG_AUTO_TRACE();
  is_scanning_allowed_ = true;
  triggering_wait_cond_var_.Broadcast();
}

void scanner::ScannerImpl::Run() {
  LOG_AUTO_TRACE();
  while (!finalyzing_) {
    if (is_scanning_allowed_) {
      const utils::UInt max_alpha = settings_.rotator_max_horyzontal();
      const utils::UInt max_beta = settings_.rotator_max_vertical();
      const utils::UInt min_alpha = settings_.rotator_min_horyzontal();
      const utils::UInt min_beta = settings_.rotator_min_vertical();
      x_rotator_.SetAngle(min_alpha);
      for (current_position_.alpha_ = min_alpha;
           current_position_.alpha_ <= max_alpha;
           ++current_position_.alpha_) {
        y_rotator_.SetAngle(min_beta);
        for (current_position_.beta_ = min_beta;
             current_position_.beta_ <= max_beta;
             ++current_position_.beta_) {
          utils::UInt distance = sensor_.GetSensorData();
          utils::positions::Incline axelerometer_data =
              axelerometer_adapter_.GetData();
          LOG_DEBUG("Scanned data [x:y=d]: " << current_position_.alpha_ << ":"
                                             << current_position_.beta_ << "="
                                             << distance);
          SendDataToServer(MakeServerMessage(distance, axelerometer_data));
          y_rotator_.ChangeAngle(1u);
        }
        x_rotator_.ChangeAngle(1u);
      }
      SendDataToServer(MakeFinalMessage());
      is_scanning_allowed_ = false;
      LOG_DEBUG("Scanning complete");
    }
    triggering_wait_cond_var_.WaitFor(finalyzing_lock_, default_waiting_timeout);
  }
}

void scanner::ScannerImpl::Join() {
  LOG_AUTO_TRACE();
  is_scanning_allowed_ = false;
  finalyzing_ = true;
  triggering_wait_cond_var_.Broadcast();
}

void scanner::ScannerImpl::SetServerMessageHandler(
    server_message_handler::ServerMessageHandler* message_handler) {
  LOG_AUTO_TRACE();
  message_handler_ = message_handler;
}

messages::SensorDataMessage scanner::ScannerImpl::MakeServerMessage(
    utils::UInt distance, utils::positions::Incline axelerometer_data) {
  LOG_AUTO_TRACE();
  return messages::SensorDataMessage(distance, current_position_ + axelerometer_data);
}

messages::SensorDataMessage scanner::ScannerImpl::MakeFinalMessage() {
  LOG_AUTO_TRACE();
  utils::positions::Incline empty_incline;
  return messages::SensorDataMessage(0, empty_incline, true);
}

void scanner::ScannerImpl::SendDataToServer(
    const messages::SensorDataMessage& message) const {
  LOG_AUTO_TRACE();
  message_handler_->SendMessageToServer(
      new messages::SensorDataMessage(message));
}
