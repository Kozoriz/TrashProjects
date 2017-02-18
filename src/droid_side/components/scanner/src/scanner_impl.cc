#include "scanner/scanner_impl.h"
#include "server_message_handler/server_message_handler.h"

#include "utils/threads/synchronization/auto_lock.h"

namespace {
utils::positions::Incline operator+(const utils::positions::Incline& a,
                                    const utils::positions::Incline& b) {
  utils::positions::Incline result;
  result.alpha_ = a.alpha_ + b.alpha_;
  result.beta_ = a.beta_ + b.beta_;
  return result;
}
}

scanner::ScannerImpl::ScannerImpl(
    const sensor_adapter::SensorAdapter& sensor_adapter,
    const servo_adapter::ServoAdapter& x_servo_adapter,
    const servo_adapter::ServoAdapter& y_servo_adapter,
    const axelerometer_adapter::AxelerometerAdapter& axelerometer_adapter,
    const utils::Profile& settings)
    : sensor_(sensor_adapter)
    , x_rotator_(x_servo_adapter)
    , y_rotator_(y_servo_adapter)
    , axelerometer_adapter_(axelerometer_adapter)
    , finalyzing_(false)
    , settings_(settings) {
  current_position_.alpha_ = 0;
  current_position_.beta_ = 0;
}

scanner::ScannerImpl::~ScannerImpl() {
  utils::synchronization::AutoLock auto_lock(finalyzing_lock_);
  finalyzing_ = true;
}

void scanner::ScannerImpl::OnScanningTriggered() {
  is_scanning_allowed_ = true;
}

void scanner::ScannerImpl::Run() {
  while (!finalyzing_) {
    utils::synchronization::AutoLock auto_lock(finalyzing_lock_);
    if (is_scanning_allowed_) {
      const utils::UInt max_alpha = settings_.rotator_max_horyzontal();
      const utils::UInt max_beta = settings_.rotator_max_vertical();
      const utils::UInt min_alpha = settings_.rotator_min_horyzontal();
      const utils::UInt min_beta = settings_.rotator_min_vertical();
      for (current_position_.alpha_ = min_alpha;
           current_position_.alpha_ <= max_alpha;
           ++current_position_.alpha_) {
        for (current_position_.beta_ = min_beta;
             current_position_.beta_ <= max_beta;
             ++current_position_.beta_) {
          utils::UInt distance = sensor_.GetSensorData();
          utils::positions::Incline axelerometer_data =
              axelerometer_adapter_.GetData();
          SendDataToServer(MakeServerMessage(distance, axelerometer_data));
        }
      }
      SendDataToServer(MakeFinalMessage());
      is_scanning_allowed_ = false;
    }
  }
}

void scanner::ScannerImpl::Join() {
  finalyzing_ = true;
}

void scanner::ScannerImpl::SetServerMessageHandler(
    server_message_handler::ServerMessageHandler* message_handler) {
  message_handler_ = message_handler;
}

scanner::SensorDataMessage scanner::ScannerImpl::MakeServerMessage(
    utils::UInt distance, utils::positions::Incline axelerometer_data) {
  return SensorDataMessage(distance, current_position_ + axelerometer_data);
}

scanner::SensorDataMessage scanner::ScannerImpl::MakeFinalMessage() {
  utils::positions::Incline empty_incline;
  return SensorDataMessage(0, empty_incline, true);
}

void scanner::ScannerImpl::SendDataToServer(
    const scanner::SensorDataMessage& message) const {
  message_handler_->SendMessageToServer(
      new scanner::SensorDataMessage(message));
}
