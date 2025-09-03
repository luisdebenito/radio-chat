#pragma once
#include <string>
#include <vector>

//@brief Encodes string to waveform using BPSK
class WaveFormEncoder {
public:
  WaveFormEncoder(double sampleRate = 44100, double bitDuration = 0.01,
                  double carrierFreq = 1000.0);

  std::vector<float> encode(const std::string &packageStr);

private:
  double sampleRate;
  double bitDuration;
  double carrierFreq;

  void appendBit(std::vector<float> &waveform, bool bit);
};
