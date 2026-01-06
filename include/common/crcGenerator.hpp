#pragma once
#include <cstdint>
#include <string>

class CRCGenerator {
public:
  static uint32_t compute(const std::string &text, const uint64_t timestamp);
};