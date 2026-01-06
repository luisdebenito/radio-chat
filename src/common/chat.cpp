#include "../../include/common/chat.hpp"

void Chat::addMessage(const std::string &text, bool sent) {
  messages.push_back({text, sent});
}

const std::vector<Chat::Message> &Chat::getMessages() const { return messages; }
