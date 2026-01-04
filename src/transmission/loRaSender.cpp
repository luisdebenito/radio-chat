#include "loRaSender.hpp"
#include <chrono>
#include <iostream>
#include <thread>

LoRaSender::LoRaSender(PackageQueue &queue, const std::string &devicePort,
                       int baudRate)
    : queue(queue), devicePort(devicePort), baudRate(baudRate), running(false) {
}

LoRaSender::~LoRaSender() {
  stop();
  if (senderThread.joinable())
    senderThread.join();
}

void LoRaSender::start() {
  running = true;
  senderThread = std::thread(&LoRaSender::run, this);
}

void LoRaSender::stop() { running = false; }

void LoRaSender::run() {
  while (running) {
    if (!queue.empty()) {
      Package pkg = queue.pop();
      if (!sendPackage(pkg)) {
        std::cerr << "[LoRaSender] Failed to send package " << pkg.getIndex()
                  << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }
}

bool LoRaSender::sendPackage(const Package &pkg) {
  // Replace with your USB LoRa write function
  std::string data = pkg.serializeToSend();
  std::cout << "[LoRa SEND] " << data << std::endl;
  // TODO: send 'data' to the LoRa modem
  return true; // return false if send failed
}
