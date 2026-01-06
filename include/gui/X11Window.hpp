#pragma once
#include "../common/chat.hpp"
#include <X11/Xlib.h>
#include <string>

class X11Window {
public:
  X11Window(const std::string &title, int width, int height, Chat &chatRef);
  ~X11Window();

  bool isValid() const;
  bool pollClose();
  bool pollLine(std::string &out); // ENTER → returns line

  void redraw();

  Display *display = nullptr;
  Window window = 0;
  GC gc;
  int screen = 0;
  int width;
  int height;

  Atom wmDeleteMessage;
  std::string inputBuffer;
  bool lineReady = false;

  Chat &chat;
};
