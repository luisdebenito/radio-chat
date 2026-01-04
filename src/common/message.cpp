#include "../../include/common/message.hpp"
#include "../../include/common/idGenerator.hpp"

Message::Message(std::string payload)
    : id(IdGenerator::generate()), date(std::chrono::system_clock::now()),
      payload(std::move(payload)) {}

const std::string &Message::getId() const { return id; }

const std::chrono::system_clock::time_point &Message::getDate() const {
  return date;
}

const std::string &Message::getPayload() const { return payload; }
