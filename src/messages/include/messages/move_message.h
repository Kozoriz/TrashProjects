#pragma once

#include "messages/message.h"
#include "utils/structures/position.h"

namespace messages {
/**
 * @brief The MoveType enum - with values in 0xmask for 4-5 bits ob Byte
 */
enum class MoveType {
  INVALID_TYPE = 0x00,  // 000 000 00
  ROTATE = 0x04,        // 000 001 00
  MOVE_FORWARD = 0x08   // 000 010 00
};
const utils::Byte kMoveTypeMask = 0x1C;  // 000 111 00

class MoveMessage : public Message {
 public:
  MoveMessage()
      : messages::Message(messages::MessageType::MOVE)
      , move_type_(MoveType::INVALID_TYPE) {}

  MoveMessage(const MoveType move_type, const utils::Int16 value)
      : messages::Message(messages::MessageType::MOVE)
      , move_type_(move_type)
      , value_(value) {
    raw_data_array_[0] |= static_cast<utils::Byte>(move_type_);
    raw_data_array_[1] = static_cast<utils::Byte>((value_ & 0xFF00) >> 8);
    raw_data_array_[2] = static_cast<utils::Byte>(value_ & 0x00FF);
  }

  MoveMessage(const utils::ByteArray& raw_data) : messages::Message(raw_data) {
    move_type_ = static_cast<MoveType>(raw_data_array_[0] & kMoveTypeMask);
    value_ = static_cast<utils::Int16>(raw_data_array_[1]) << 8;
    value_ += static_cast<utils::Int16>(raw_data_array_[2]);
  }

  //  /**
  //   * @brief ToRawData -- TODO test it
  //   * @return
  //   */
  //  utils::ByteArray ToRawData() const override {
  //    // Push message type mask : 0x11100000
  //    utils::Byte header = static_cast<utils::Byte>(type_);
  //    // Push move type mask : 0x00011100
  //    header |= static_cast<utils::Byte>(move_type_);

  //    // Create 2nd Byte from value
  //    utils::Byte value_1 = static_cast<utils::Byte>((value_ & 0xF0) >> 8);
  //    // Create 3rd Byte from value
  //    utils::Byte value_2 = static_cast<utils::Byte>(value_ & 0xF0);

  //    return {header, value_1, value_2};
  //  }

  MoveType move_type() const {
    return move_type_;
  }
  utils::Int16 value() const {
    return value_;
  }

 protected:
  MoveType move_type_;
  /**
   * @brief value_ - angle/distace
   */
  utils::Int16 value_;
};
}  // namespace messages
