#include "waveFormDecoder.hpp"
#include <cmath>
#include <cstdint>

WaveFormDecoder::WaveFormDecoder(double sampleRate, double bitDuration,
                                 double carrierFreq)
    : sampleRate(sampleRate), bitDuration(bitDuration),
      carrierFreq(carrierFreq) {}

bool WaveFormDecoder::decodeBit(const std::vector<float> &waveform,
                                size_t startIndex) {
  size_t numSamples = static_cast<size_t>(bitDuration * sampleRate);
  double sum = 0.0;

  for (size_t n = 0; n < numSamples; ++n) {
    double t = static_cast<double>(n) / sampleRate;
    double refCarrier = std::sin(2 * M_PI * carrierFreq * t);
    sum += waveform[startIndex + n] * refCarrier;
  }

  return (sum < 0);
  // negative correlation → phase = π → bit = 1
}

std::string WaveFormDecoder::decode(const std::vector<float> &waveform) {
  size_t numSamplesPerBit = static_cast<size_t>(bitDuration * sampleRate);
  size_t totalBits = waveform.size() / numSamplesPerBit;

  std::string result;
  result.reserve(totalBits / 8);

  uint8_t currentByte = 0;

  for (size_t bitIndex = 0; bitIndex < totalBits; ++bitIndex) {
    bool bit = decodeBit(waveform, bitIndex * numSamplesPerBit);

    currentByte = (currentByte << 1) | (bit ? 1 : 0);

    if ((bitIndex + 1) % 8 == 0) {
      result.push_back(static_cast<char>(currentByte));
      currentByte = 0;
    }
  }

  return result;
}
