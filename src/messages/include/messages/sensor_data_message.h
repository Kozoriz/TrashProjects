#pragma once

#include "messages/message.h"
#include "utils/structures/position.h"

namespace messages {

const utils::Byte kFinalFlagMask = 0x10;

class SensorDataMessage : public Message {
 public:
  SensorDataMessage(const utils::UInt16 distance,
                    const utils::positions::Incline& incline,
                    const bool is_final = false)
      : messages::Message(messages::MessageType::SENSOR_DATA)
      , final_message_(is_final)
      , distance_(distance)
      , sensor_position_(incline) {
    raw_data_array_[0] |= (static_cast<utils::Byte>(final_message_) << 4);
    raw_data_array_[1] = static_cast<utils::Byte>((distance_ & 0xFF00) >> 8);
    raw_data_array_[2] = static_cast<utils::Byte>(distance_ & 0x00FF);
    raw_data_array_[3] =
        (UINT8_MAX < incline.alpha_)
            ? UINT8_MAX
            : static_cast<utils::Byte>(incline.alpha_ & 0x00FF);
    raw_data_array_[4] = (UINT8_MAX < incline.beta_)
                             ? UINT8_MAX
                             : static_cast<utils::Byte>(incline.beta_ & 0x00FF);
  }

  SensorDataMessage(const utils::ByteArray& raw_data)
      : messages::Message(raw_data) {
    final_message_ =
        static_cast<bool>((raw_data_array_[0] & kFinalFlagMask) >> 4);

    distance_ = static_cast<utils::UInt16>(raw_data_array_[1]) << 8;
    distance_ += static_cast<utils::UInt16>(raw_data_array_[2]);

    sensor_position_.alpha_ = static_cast<utils::UInt16>(raw_data_array_[3]);
    sensor_position_.beta_ = static_cast<utils::UInt16>(raw_data_array_[4]);
  }

 protected:
  bool final_message_;
  utils::UInt16 distance_;
  utils::positions::Incline sensor_position_;
};
}  // namespace messages
