#pragma once
#include <chrono>
#include <string>

class Message {
public:
  Message(std::string payload);

  const std::string &getId() const;
  const std::chrono::system_clock::time_point &getDate() const;
  const std::string &getPayload() const;

private:
  std::string id;
  std::chrono::system_clock::time_point date;
  std::string payload;
};
