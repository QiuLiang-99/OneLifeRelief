#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <chrono>
#include <cstdint>
#include <iostream>

class Snowflake {
  public:
    explicit Snowflake(uint64_t workerId);
    uint64_t generateId();

  private:
    uint64_t getCurrentTimestamp();
    uint64_t tilNextMillis(uint64_t lastTimestamp);

  private:
    uint64_t workerId;
    uint64_t sequence      = 0;
    uint64_t lastTimestamp = 0;
};
#endif // SNOWFLAKE_H