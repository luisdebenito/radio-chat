#include "transmissionManager.hpp"
#include "packageBuilder.hpp"
#include "packageQueue.hpp"
#include <vector>

TransmissionManager::TransmissionManager(PackageBuilder &packageBuilder,
                                         PackageQueue &queue)
    : packageBuilder(packageBuilder), packageQueue(queue) {}

void TransmissionManager::sendText(const std::string &text) {
  Message msg(text);

  std::vector<Package> packages = this->packageBuilder.build(msg);

  for (auto &p : packages) {
    packageQueue.push(std::move(p));
  }
}