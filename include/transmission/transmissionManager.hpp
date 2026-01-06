#pragma once
#include "packageQueue.hpp"
#include <string>

class TransmissionManager {
public:
  TransmissionManager(PackageQueue &packageQueue);

  void sendText(const std::string &text);

private:
  PackageQueue &packageQueue;
};
