#pragma once

#include "messages/sensor_data_message.h"

class MessageListener {
 public:
  virtual void OnDataMessageReceived(
      const messages::SensorDataMessage& message) = 0;
  virtual void OnFinalMessageReceived() = 0;
};
