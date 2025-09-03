#pragma once
#include <string>
#include <vector>

class WaveFormDecoder {
public:
  WaveFormDecoder(double sampleRate = 44100, double bitDuration = 0.01,
                  double carrierFreq = 1000.0);

  std::string decode(const std::vector<float> &waveform);

private:
  double sampleRate;
  double bitDuration;
  double carrierFreq;

  bool decodeBit(const std::vector<float> &waveform, size_t startIndex);
};
