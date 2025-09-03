#include "transmissionManager.hpp"
#include "packageBuilder.hpp"
#include "waveFormEncoder.hpp"
#include "waveFormQueue.hpp"
#include <vector>

TransmissionManager::TransmissionManager(PackageBuilder &packageBuilder,
                                         WaveFormEncoder &waveFormEncoder,
                                         WaveFormQueue &waveFormQueue)
    : packageBuilder(packageBuilder), waveFormEncoder(waveFormEncoder),
      waveFormQueue(waveFormQueue) {}

void TransmissionManager::sendText(const std::string &text) {
  Message msg(text);

  std::vector<Package> packages = this->packageBuilder.build(msg);

  for (const auto &p : packages) {
    auto waveform = waveFormEncoder.encode(p.serializeToSend());
    waveFormQueue.push(std::move(waveform));
  }
}