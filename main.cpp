#include "include/common/config.hpp"
#include "include/gui/X11Window.hpp"
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

  PackageBuilder builder(maxBytes);
  PackageQueue queue;
  TransmissionManager trnsmManager(builder, queue);

  LoRaSender sender(queue, devicePort, baudRate);
  sender.start();

  X11Window window("Decentralized LoRa Messenger", 400, 600);
  if (!window.isValid()) {
    return 1;
  }

  std::string input;
  while (true) {
    std::getline(std::cin, input);

    if (input.empty())
      continue;
    if (input == "exit")
      break;

    trnsmManager.sendText(input);
  }

  sender.stop();
  return 0;
}
