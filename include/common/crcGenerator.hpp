#pragma once
#include <chrono>
#include <cstdint>
#include <string>

class CRCGenerator {
public:
  static uint32_t compute(const std::string &id, const std::string &text,
                          const std::chrono::system_clock::time_point &date);
};