#include "../../include/gui/X11Window.hpp"
#include <unistd.h>

X11Window::X11Window(const std::string &title, int width, int height) {
  display = XOpenDisplay(nullptr);
  if (!display)
    return;

  screen = DefaultScreen(display);

  window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100,
                               width, height, 1, BlackPixel(display, screen),
                               WhitePixel(display, screen));

  XStoreName(display, window, title.c_str());
  XMapWindow(display, window);
  XFlush(display);
}

X11Window::~X11Window() {
  if (display) {
    XCloseDisplay(display);
  }
}

bool X11Window::isValid() const { return display != nullptr; }
