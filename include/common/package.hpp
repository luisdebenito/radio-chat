#pragma once
#include <chrono>
#include <cstdint>
#include <string>

class Package {
public:
  Package(const std::string &messageId,
          const std::chrono::system_clock::time_point &date, uint32_t index,
          uint32_t total, const std::string &fragment);

  const std::string &getMessageId() const;
  uint32_t getIndex() const;
  uint32_t getTotal() const;
  const std::string &getFragment() const;
  uint32_t getCRC() const;
  const std::chrono::system_clock::time_point &getDate() const;
  const std::string serializeForCRC() const;
  const std::string serializeToSend() const;

private:
  std::string messageId;
  std::chrono::system_clock::time_point date;
  uint32_t index;
  uint32_t total;
  std::string fragment;
  uint32_t crc;
  static const std::string SEPARATOR;

  uint32_t computeCRC() const; // internal helper
};
