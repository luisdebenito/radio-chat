#pragma once
#include "../common/package.hpp"
#include "packageQueue.hpp"
#include <atomic>
#include <string>
#include <thread>

class LoRaSender {
public:
  LoRaSender(PackageQueue &queue, const std::string &devicePort,
             int baudRate = 9600);
  ~LoRaSender();

  void start(); // start sending in a separate thread
  void stop();  // stop sending

private:
  void run();

  PackageQueue &queue;
  std::string devicePort;
  int baudRate;
  std::thread senderThread;
  std::atomic<bool> running;

  bool sendPackage(const Package &pkg); // low-level send to LoRa
};
