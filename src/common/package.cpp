#include "../../include/common/package.hpp"
#include "../../include/common/crcGenerator.hpp"
#include <string>

const std::string Package::SEPARATOR = "|_|";

Package::Package(const std::string &messageId,
                 const std::chrono::system_clock::time_point &date,
                 uint32_t index, uint32_t total, const std::string &fragment)
    : messageId(messageId), date(date), index(index), total(total),
      fragment(fragment), crc(computeCRC()) {}

uint32_t Package::computeCRC() const {
  return CRCGenerator::compute(serializeForCRC());
}

const std::string Package::serializeForCRC() const {
  return messageId +
         std::to_string(std::chrono::system_clock::to_time_t(date)) +
         std::to_string(index) + std::to_string(total) + fragment;
}

/// @brief [ID][DATE][INDEX][TOTAL][PAYLOAD][CRC]
const std::string Package::serializeToSend() const {
  return messageId + this->SEPARATOR +
         std::to_string(std::chrono::system_clock::to_time_t(date)) +
         this->SEPARATOR + std::to_string(index) + this->SEPARATOR +
         std::to_string(total) + this->SEPARATOR + fragment + this->SEPARATOR +
         std::to_string(crc);
}

const std::string &Package::getMessageId() const { return messageId; }
uint32_t Package::getIndex() const { return index; }
uint32_t Package::getTotal() const { return total; }
const std::string &Package::getFragment() const { return fragment; }
uint32_t Package::getCRC() const { return crc; }
