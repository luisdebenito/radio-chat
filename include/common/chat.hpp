#pragma once
#include <string>
#include <vector>

class Chat {
public:
  struct Message {
    std::string text;
    bool sent; // true = sent, false = received
  };

  explicit Chat(int maxChatHistory);

  void addMessage(const std::string &text, bool sent);
  const std::vector<Message> &getMessages() const;

private:
  std::vector<Message> messages;
  int maxChatHistory;
};
