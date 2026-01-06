#include "include/common/chat.hpp" // include the Chat class
#include "include/common/config.hpp"
#include "include/gui/X11Window.hpp"
#include "include/transmission/loRaSender.hpp"
#include "include/transmission/packageQueue.hpp"
#include "include/transmission/transmissionManager.hpp"

#include <string>

int main() {
  Config cfg("build/config.conf");
  std::string devicePort = cfg.getString("devicePort", "/dev/ttyUSB0");
  int baudRate = cfg.getInt("baudRate", 9600);

  PackageQueue queue;
  Chat chat;

  TransmissionManager trnsmManager(queue);
  LoRaSender sender(queue, devicePort, baudRate);

  X11Window window("Decentralized LoRa Messenger", 400, 600, chat);
  if (!window.isValid()) {
    return 1;
  }

  std::string text;
  sender.start();

  while (true) {
    if (window.pollClose())
      break;

    if (window.pollLine(text)) {
      chat.addMessage(text, true);
      trnsmManager.sendText(text);
      window.redraw();
    }
  }

  sender.stop();
  return 0;
}
