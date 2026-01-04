#include "../../include/transmission/packageBuilder.hpp"
#include <chrono>

PackageBuilder::PackageBuilder(uint32_t maxFragmentSize)
    : maxFragmentSize(maxFragmentSize) {}

std::vector<Package> PackageBuilder::build(const Message &msg) const {
  const std::string &payload = msg.getPayload();
  const std::string &id = msg.getId();
  const std::chrono::system_clock::time_point &date = msg.getDate();

  uint32_t total = (payload.size() + maxFragmentSize - 1) / maxFragmentSize;
  std::vector<Package> result;
  result.reserve(total);

  for (uint32_t i = 0; i < total; ++i) {
    uint32_t start = i * maxFragmentSize;
    std::string fragment = payload.substr(start, maxFragmentSize);

    result.emplace_back(id, date, i, total, fragment);
  }

  return result;
}
