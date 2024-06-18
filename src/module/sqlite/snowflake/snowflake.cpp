#include "snowflake.h"
Snowflake::Snowflake(uint64_t workerId) : workerId(workerId) {}
uint64_t Snowflake::generateId() {
  uint64_t timestamp = getCurrentTimestamp();
  if (timestamp < lastTimestamp) {
    throw std::runtime_error("Clock moved backwards");
  }
  if (timestamp == lastTimestamp) {
    sequence = (sequence + 1) & 0xfff;
    if (sequence == 0) {
      timestamp = tilNextMillis(lastTimestamp);
    }
  } else {
    sequence = 0;
  }
  lastTimestamp = timestamp;
  return ((timestamp - 1288834974657L) << 22) | (workerId << 12) | sequence;
}
uint64_t Snowflake::getCurrentTimestamp() {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

uint64_t Snowflake::tilNextMillis(uint64_t lastTimestamp) {
  uint64_t timestamp = getCurrentTimestamp();
  while (timestamp <= lastTimestamp) {
    timestamp = getCurrentTimestamp();
  }
  return timestamp;
}