#include "include/common/config.hpp"
#include "include/transmission/loRaSender.hpp"
#include "include/transmission/packageBuilder.hpp"
#include "include/transmission/packageQueue.hpp"
#include "include/transmission/transmissionManager.hpp"

#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <unistd.h>

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

  Display *display = XOpenDisplay(nullptr);
  if (!display) {
    return 1;
  }

  int screen = DefaultScreen(display);

  Window window = XCreateSimpleWindow(
      display, RootWindow(display, screen), 100, 100, // x, y
      400, 300,                                       // width, height
      1,                                              // border width
      BlackPixel(display, screen), WhitePixel(display, screen));

  XStoreName(display, window, "Decentralized LoRa Messenger");
  XMapWindow(display, window);
  XFlush(display);

  std::cout << "Welcome \n";
  while (true) {
    std::getline(std::cin, input);

    if (input.empty())
      continue;

    if (input == "exit")
      break;

    trnsmManager.sendText(input);
  }

  XCloseDisplay(display);

  sender.stop(); // stop sender gracefully
  return 0;
}
