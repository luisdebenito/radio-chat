#include "../../include/gui/X11Window.hpp"
#include <X11/Xutil.h>
#include <X11/keysym.h>

X11Window::X11Window(const std::string &title, int w, int h)
    : width(w), height(h) {
  display = XOpenDisplay(nullptr);
  if (!display)
    return;

  screen = DefaultScreen(display);

  window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100,
                               width, height, 1, BlackPixel(display, screen),
                               WhitePixel(display, screen));

  XStoreName(display, window, title.c_str());

  wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &wmDeleteMessage, 1);

  XSelectInput(display, window,
               ExposureMask | KeyPressMask | StructureNotifyMask);

  gc = XCreateGC(display, window, 0, nullptr);

  XMapWindow(display, window);
  XFlush(display);
}

X11Window::~X11Window() {
  if (display) {
    XFreeGC(display, gc);
    XCloseDisplay(display);
  }
}

bool X11Window::isValid() const { return display != nullptr; }

void X11Window::redraw() {
  XClearWindow(display, window);

  int lineY = height - 20;

  // Separator line
  XDrawLine(display, window, gc, 0, lineY, width, lineY);

  // Input text
  XDrawString(display, window, gc, 5, height - 5, inputBuffer.c_str(),
              inputBuffer.size());

  XFlush(display);
}

bool X11Window::pollClose() {
  while (XPending(display)) {
    XEvent ev;
    XNextEvent(display, &ev);

    if (ev.type == ClientMessage &&
        (Atom)ev.xclient.data.l[0] == wmDeleteMessage) {
      return true;
    }

    if (ev.type == Expose) {
      redraw();
    }

    if (ev.type == KeyPress) {
      KeySym key;
      char buf[8];
      int len = XLookupString(&ev.xkey, buf, sizeof(buf), &key, nullptr);

      if (key == XK_BackSpace && !inputBuffer.empty()) {
        inputBuffer.pop_back();
      } else if (key == XK_Return) {
        lineReady = true;
      } else if (len == 1 && buf[0] >= 32 && buf[0] <= 126) {
        inputBuffer += buf[0];
      }
      redraw();
    }
  }
  return false;
}

bool X11Window::pollLine(std::string &out) {
  if (!lineReady)
    return false;

  out = inputBuffer;
  inputBuffer.clear();
  lineReady = false;
  redraw();
  return true;
}
