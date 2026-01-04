#pragma once
#include "message.hpp"
#include <cstdint>

class CRCGenerator {
public:
  static uint32_t compute(const Message &message);
};