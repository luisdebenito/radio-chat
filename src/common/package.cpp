#include "../../include/common/package.hpp"
#include "../../include/common/crcGenerator.hpp"
#include <string>

const std::string Package::SEPARATOR = "|_|";

Package::Package(const std::string &t)
    : text(t), date(std::chrono::system_clock::now()),
      crc(CRCGenerator::compute(text, getDateAsInt())) {}

/// @brief [ID][DATE][PAYLOAD][CRC]
const std::string Package::serializeToSend() const {
  return std::to_string(getDateAsInt()) + this->SEPARATOR + text +
         this->SEPARATOR + std::to_string(crc);
}

const uint64_t Package::getDateAsInt() const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             date.time_since_epoch())
      .count();
}

const std::string &Package::getText() const { return text; }
