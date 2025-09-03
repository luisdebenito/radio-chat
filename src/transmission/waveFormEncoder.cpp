#include "waveFormEncoder.hpp"
#include <cmath>
#include <cstdint>

WaveFormEncoder::WaveFormEncoder(double sampleRate, double bitDuration,
                                 double carrierFreq)
    : sampleRate(sampleRate), bitDuration(bitDuration),
      carrierFreq(carrierFreq) {}

std::vector<float> WaveFormEncoder::encode(const std::string &packageStr) {
  std::vector<float> waveform;
  for (char c : packageStr) {
    uint8_t byte = static_cast<uint8_t>(c);
    for (int i = 7; i >= 0; --i) {
      bool bit = (byte >> i) & 0x01;
      appendBit(waveform, bit);
    }
  }
  return waveform;
}

void WaveFormEncoder::appendBit(std::vector<float> &waveform, bool bit) {
  size_t numSamples = static_cast<size_t>(bitDuration * sampleRate);
  double phase = bit ? M_PI : 0.0;
  for (size_t n = 0; n < numSamples; ++n) {
    double t = static_cast<double>(n) / sampleRate;
    waveform.push_back(
        static_cast<float>(std::sin(2 * M_PI * carrierFreq * t + phase)));
  }
}
