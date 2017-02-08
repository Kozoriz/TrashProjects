#pragma once

#include "server_message_handler/message.h"
#include "utils/structures/position.h"

namespace mover {
/**
 * @brief The MoveType enum - with values in 0xmask for 4-5 bits ob Byte
 */
enum class MoveType {
  ROTATE = 0x08,       // 000 01 000
  MOVE_FORWARD = 0x10  // 000 10 000
};
const utils::Byte kMoveTypeMask = 0x18;  // 000 11 000

class MoveMessage : public server_message_handler::Message {
 public:
  MoveMessage()
      : server_message_handler::Message(
            server_message_handler::MessageType::MOVE) {}
  MoveMessage(const MoveType move_type,
              const utils::Int16 value)
      : server_message_handler::Message(server_message_handler::MessageType::MOVE)
      , move_type_(move_type)
      , value_(value) {}

  MoveMessage(const utils::ByteArray& raw_data)
      : server_message_handler::Message(raw_data) {
    move_type_ = static_cast<MoveType>(raw_data[0] & kMoveTypeMask);
    value_ = static_cast<utils::Int>(raw_data[1]) << 8;
    value_ += static_cast<utils::Int>(raw_data[2]);
  }
  /**
   * @brief ToRawData -- TODO test it
   * @return
   */
  utils::ByteArray ToRawData() const override {
    // Push message type mask : 0x11100000
    utils::Byte header = static_cast<utils::Byte>(type_);
    // Push move type mask : 0x00011000
    header |= static_cast<utils::Byte>(move_type_);

    // Create 2nd Byte from value
    utils::Byte value_1 = static_cast<utils::Byte>((value_ & 0xF0) >> 8);
    // Create 3rd Byte from value
    utils::Byte value_2 = static_cast<utils::Byte>(value_ & 0xF0);

    return {header, value_1, value_2};
  }

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
}  // namespace mover
