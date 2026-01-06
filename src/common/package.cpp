#include "../../include/common/package.hpp"
#include "../../include/common/crcGenerator.hpp"
#include <string>

const std::string Package::SEPARATOR = "|_|";

Package::Package(const std::string &t)
    : text(t), date(std::chrono::system_clock::now()),
      crc(CRCGenerator::compute(text, date)) {}

/// @brief [ID][DATE][PAYLOAD][CRC]
const std::string Package::serializeToSend() const {
  return std::to_string(std::chrono::system_clock::to_time_t(date)) +
         this->SEPARATOR + text + this->SEPARATOR + std::to_string(crc);
}

const std::chrono::system_clock::time_point &Package::getDate() const {
  return date;
}

const std::string &Package::getText() const { return text; }
