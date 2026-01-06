#include "../../include/common/crcGenerator.hpp"
#include <cstdint>
#include <string>
#include <vector>

// Simple CRC-32 (IEEE 802.3) implementation
static uint32_t crc32(const uint8_t *data, size_t len) {
  uint32_t crc = 0xFFFFFFFF;

  for (size_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (int j = 0; j < 8; j++) {
      uint32_t mask = -(crc & 1);
      crc = (crc >> 1) ^ (0xEDB88320 & mask);
    }
  }

  return ~crc;
}

// New compute method: pass id, text, and date
uint32_t CRCGenerator::compute(const std::string &text,
                               const uint64_t timestamp) {

  // Concatenate data as bytes
  std::vector<uint8_t> buffer;

  auto append_str = [&](const std::string &s) {
    buffer.insert(buffer.end(), s.begin(), s.end());
  };

  auto append_uint64 = [&](uint64_t v) {
    for (int i = 0; i < 8; i++)
      buffer.push_back((v >> (i * 8)) & 0xFF);
  };

  append_uint64(timestamp);
  append_str(text);

  return crc32(buffer.data(), buffer.size());
}
