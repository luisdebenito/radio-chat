#pragma once
#include <vector>

class SDRTransmitter {
public:
  SDRTransmitter(double frequencyHz, double sampleRateHz, double gain);

  bool openDevice();
  void closeDevice();
  void transmit(const std::vector<float> &samples);

private:
  double frequencyHz_;
  double sampleRateHz_;
  double gain_;
  void *deviceHandle_;
};
