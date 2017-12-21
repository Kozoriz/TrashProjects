#pragma once

#include "utils/containers/vector.h"
#include "utils/structures/position.h"

namespace messages {
/**
 * @brief The MessageType enum - with values 0xmask for 1-3 bits of Byte
 */
enum class MessageType {
  MOVE = 0x20,         // 001 00000
  SENSOR_DATA = 0x40,  // 010 00000
  START_SCAN = 0x60,   // 011 00000
  STOP_PROGRAM = 0x80  // 100 00000
};
const utils::Byte kMessageTypeMask = 0xE0;  // 111 00000
const utils::Int kMaxRawDataSize = 5u;

class Message {
  /*
   * First Byte always header data (message type description)
   *
   * Message from server
   * |3|3|2reserved|16| = 24bits = 3Bytes
   * 3 - Message type
   * 3 - Move type
   * 16 - Move value (int)
   *
   * Message to server
   * |3|1|4reserved|16|16| = 40bits = 5Bytes
   * 3 - Message type
   * 1 - final message
   * 16 - distance
   * 16=8*2 - incline (2 angles) 0-180
   */
 public:
  Message(const MessageType type) : type_(type) {
    raw_data_array_.resize(kMaxRawDataSize);
    raw_data_array_[0] = static_cast<utils::Byte>(type_);
  }

  Message(const utils::ByteArray& raw_data) {
    raw_data_array_ = raw_data;
    raw_data_array_.resize(kMaxRawDataSize);
    type_ = static_cast<MessageType>(raw_data_array_[0] & kMessageTypeMask);
  }

  virtual const utils::ByteArray& ToRawData() const {
    return raw_data_array_;
  }

  MessageType type() {
    return type_;
  }

 protected:
  MessageType type_;
  utils::ByteArray raw_data_array_;
};
}  // namespace messages
