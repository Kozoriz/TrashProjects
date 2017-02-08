#include "scanner/scanner_impl.h"
#include "server_message_handler/server_message_handler.h"

#include "utils/synchronization/auto_lock.h"

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
    const axelerometer_adapter::AxelerometerAdapter& axelerometer_adapter)
    : sensor_(sensor_adapter)
    , x_rotator_(x_servo_adapter)
    , y_rotator_(y_servo_adapter)
    , axelerometer_adapter_(axelerometer_adapter)
    , finalyzing_(false) {
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
      // TODO use profiler for max x/y
      for (current_position_.alpha_; current_position_.alpha_ <= 179;
           ++current_position_.alpha_) {
        for (current_position_.beta_; current_position_.beta_ <= 180;
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
