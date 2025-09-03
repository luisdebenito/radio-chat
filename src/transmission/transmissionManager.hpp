#pragma once
#include "packageBuilder.hpp"
#include "waveFormEncoder.hpp"
#include "waveFormQueue.hpp"
#include <string>

class TransmissionManager {
public:
  TransmissionManager(PackageBuilder &packageBuilder,
                      WaveFormEncoder &waveFormEncoder,
                      WaveFormQueue &waveFormQueue);

  void sendText(const std::string &text);

private:
  WaveFormEncoder &waveFormEncoder;
  PackageBuilder &packageBuilder;
  WaveFormQueue &waveFormQueue;
};
