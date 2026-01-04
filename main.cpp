#include "src/transmission/loRaSender.hpp"
#include "src/transmission/packageBuilder.hpp"
#include "src/transmission/packageQueue.hpp"
#include "src/transmission/transmissionManager.hpp"

#include <iostream>
#include <string>

int main() {
  std::string input;
  PackageBuilder builder(64); // max bytes per package
  PackageQueue queue;

  TransmissionManager trnsmManager(builder, queue);
  LoRaSender sender(queue, "/dev/ttyUSB0", 9600);
  sender.start(); // starts sending in background

  while (true) {
    std::cout << "Enter message: ";
    std::getline(std::cin, input);

    if (input.empty())
      continue;

    if (input == "exit")
      break;

    trnsmManager.sendText(input);
  }

  sender.stop(); // stop sender gracefully
  return 0;
}
