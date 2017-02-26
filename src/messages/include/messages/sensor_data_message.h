#pragma once

#include "messages/message.h"
#include "utils/structures/position.h"

namespace messages {
class SensorDataMessage : public Message {
 public:
  SensorDataMessage(const utils::UInt16 distance,
                    const utils::positions::Incline& incline,
                    const bool is_final = false)
      : messages::Message(
            messages::MessageType::SENSOR_DATA)
      , final_message_(is_final)
      , distance_(distance)
      , sensor_position_(incline) {}

  SensorDataMessage(const utils::ByteArray& raw_data)
      : messages::Message(raw_data) {
    final_message_ = static_cast<bool>((raw_data[0] & 0x10) >> 4);

    distance_ = static_cast<utils::UInt16>(raw_data[1] << 8);
    distance_ += static_cast<utils::UInt16>(raw_data[2]);

    sensor_position_.alpha_ = static_cast<utils::UInt16>(raw_data[3]);
    sensor_position_.beta_ = static_cast<utils::UInt16>(raw_data[4]);
  }

  utils::ByteArray ToRawData() const override {
    utils::Byte header = static_cast<utils::Byte>(type_);
    header |= static_cast<utils::Byte>(final_message_) << 4;

    utils::Byte dist_1 = static_cast<utils::Byte>((distance_ & 0xF0) >> 8);
    utils::Byte dist_2 = static_cast<utils::Byte>(distance_ & 0x0F);
    utils::Byte incline_alpha =
        (sensor_position_.alpha_ > 180)
            ? 180
            : static_cast<utils::Byte>(sensor_position_.alpha_);
    utils::Byte incline_beta =
        (sensor_position_.beta_ > 180)
            ? 180
            : static_cast<utils::Byte>(sensor_position_.alpha_);
    return {header, dist_1, dist_2, incline_alpha, incline_beta};
  }

 protected:
  bool final_message_;
  utils::UInt16 distance_;
  utils::positions::Incline sensor_position_;
};
}  // namespace messages
