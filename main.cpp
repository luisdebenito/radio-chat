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
  int maxInputSize = cfg.getInt("maxInputSize", 80);
  int windowWidth = cfg.getInt("windowWidth", 400);
  int windowHeight = cfg.getInt("windowHeight", 600);
  int maxChatHistory = cfg.getInt("maxChatHistory", 30);

  PackageQueue queue;
  Chat chat(maxChatHistory);

  TransmissionManager trnsmManager(queue);
  LoRaSender sender(queue, devicePort, baudRate);

  X11Window window("Decentralized LoRa Messenger", windowWidth, windowHeight,
                   static_cast<size_t>(maxInputSize), chat);
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
