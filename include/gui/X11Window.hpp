#pragma once
#include <X11/Xlib.h>
#include <string>

class X11Window {
public:
  X11Window(const std::string &title, int width, int height);
  ~X11Window();

  bool isValid() const;

private:
  Display *display = nullptr;
  Window window = 0;
  int screen = 0;
};
