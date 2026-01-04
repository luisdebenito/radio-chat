#include "include/common/config.hpp"
#include "include/transmission/loRaSender.hpp"
#include "include/transmission/packageBuilder.hpp"
#include "include/transmission/packageQueue.hpp"
#include "include/transmission/transmissionManager.hpp"

#include <iostream>
#include <string>

int main() {
  Config cfg("build/config.conf");
  int maxBytes = cfg.getInt("maxBytes", 64);
  std::string devicePort = cfg.getString("devicePort", "/dev/ttyUSB0");
  int baudRate = cfg.getInt("baudRate", 9600);

  std::string input;
  PackageBuilder builder(64); // max bytes per package
  PackageQueue queue;

  TransmissionManager trnsmManager(builder, queue);
  LoRaSender sender(queue, "/dev/ttyUSB0", 9600);
  sender.start(); // starts sending in background

  std::cout << "Welcome \n";
  while (true) {
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
