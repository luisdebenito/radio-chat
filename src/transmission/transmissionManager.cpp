#include "../../include/transmission/transmissionManager.hpp"
#include "../../include/transmission/packageQueue.hpp"

TransmissionManager::TransmissionManager(PackageQueue &queue)
    : packageQueue(queue) {}

void TransmissionManager::sendText(const std::string &text) {
  Package package(text);
  packageQueue.push(std::move(package));
}