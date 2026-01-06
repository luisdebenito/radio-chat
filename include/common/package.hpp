#pragma once
#include <chrono>
#include <cstdint>
#include <string>

class Package {
public:
  Package(const std::string &text);

  const uint64_t getDateAsInt() const;
  const std::string serializeToSend() const;
  const std::string &getText() const;

private:
  std::string text;
  std::chrono::system_clock::time_point date;
  uint32_t crc;
  static const std::string SEPARATOR;
};
