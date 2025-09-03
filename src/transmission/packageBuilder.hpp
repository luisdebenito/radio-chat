#pragma once
#include "../common/message.hpp"
#include "../common/package.hpp"
#include <cstdint>
#include <vector>

class PackageBuilder {
public:
  // maxFragmentSize = max bytes of payload allowed per package
  PackageBuilder(uint32_t maxFragmentSize);

  std::vector<Package> build(const Message &msg) const;

private:
  uint32_t maxFragmentSize;
};
