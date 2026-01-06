#include "../../include/common/chat.hpp"

void Chat::addMessage(const std::string &text, bool sent) {
  messages.push_back({text, sent});
  if (messages.size() > 30) {
    messages.erase(messages.begin()); // remove oldest message
  }
}

const std::vector<Chat::Message> &Chat::getMessages() const { return messages; }
