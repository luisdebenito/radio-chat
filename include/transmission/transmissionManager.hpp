#pragma once
#include "packageBuilder.hpp"
#include "packageQueue.hpp"
#include <string>

class TransmissionManager {
public:
  TransmissionManager(PackageBuilder &packageBuilder,
                      PackageQueue &packageQueue);

  void sendText(const std::string &text);

private:
  PackageBuilder &packageBuilder;
  PackageQueue &packageQueue;
};
