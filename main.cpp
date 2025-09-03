#include "src/transmission/packageBuilder.hpp"
#include "src/transmission/transmissionManager.hpp"
#include "src/transmission/waveFormEncoder.hpp"
#include "src/transmission/waveFormQueue.hpp"

#include <iostream>
#include <string>

int main() {
  std::string input;
  PackageBuilder builder(64); // max bytes per package
  WaveFormEncoder encoder;
  WaveFormQueue queue;

  TransmissionManager trnsmManager(builder, encoder, queue);

  while (true) {
    std::cout << "Enter message: ";
    std::getline(std::cin, input);

    if (input == "")
      continue;

    if (input == "exit")
      break;

    trnsmManager.sendText(input);
    std::cout << "Waveform queue size: " << queue.size() << "\n";
  }
  return 0;
}
