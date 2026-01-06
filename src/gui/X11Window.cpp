#include "../../include/gui/X11Window.hpp"
#include <X11/Xutil.h>  // Utilities like XLookupString
#include <X11/keysym.h> // Key symbol definitions (XK_Return, XK_BackSpace, etc.)

X11Window::X11Window(const std::string &title, int w, int h, size_t maxInput,
                     Chat &chatRef)
    : width(w), height(h), maxInputSize(maxInput), chat(chatRef) {

  // Open connection to X server (nullptr = default DISPLAY)
  display = XOpenDisplay(nullptr);
  if (!display)
    return;

  screen = DefaultScreen(display);

  window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100,
                               width, height, 1, BlackPixel(display, screen),
                               WhitePixel(display, screen));

  // Disable window resizing
  XSizeHints sizeHints;
  sizeHints.flags = PMinSize | PMaxSize;
  sizeHints.min_width = width;
  sizeHints.min_height = height;
  sizeHints.max_width = width;
  sizeHints.max_height = height;

  XSetWMNormalHints(display, window, &sizeHints);

  // Set window title for window manager
  XStoreName(display, window, title.c_str());

  // Prepare to handle window close button
  wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &wmDeleteMessage, 1);

  // Select events we want to handle: redraw, key press, window changes
  XSelectInput(display, window,
               ExposureMask | KeyPressMask | StructureNotifyMask);

  // Create a graphics context for drawing text/lines
  gc = XCreateGC(display, window, 0, nullptr);

  // Map window (make visible) and flush commands to server
  XMapWindow(display, window);
  XFlush(display);
}

// Destructor
X11Window::~X11Window() {
  if (display) {
    XFreeGC(display, gc);   // free graphics context
    XCloseDisplay(display); // close connection to X server
  }
}

// Check if display was successfully opened
bool X11Window::isValid() const { return display != nullptr; }

// Redraw the window
void X11Window::redraw() {
  XClearWindow(display, window); // clear window to background color

  int y = 20; // start from top for chat messages
  for (const auto &msg : chat.getMessages()) {
    int x = msg.sent ? 10
                     : width - 10 - msg.text.size() * 8; // left/right alignment
    XDrawString(display, window, gc, x, y, msg.text.c_str(), msg.text.size());
    y += 20; // next line
  }

  int lineY = height - 20; // horizontal line position 20px from bottom

  // Draw horizontal separator line
  XDrawLine(display, window, gc, 0, lineY, width, lineY);

  // Draw input text below the line, with margin 5px
  XDrawString(display, window, gc, 5, height - 5, inputBuffer.c_str(),
              inputBuffer.size());

  XFlush(display); // send drawing commands immediately
}

// Poll for close event, key presses, or redraw
bool X11Window::pollClose() {
  while (XPending(display)) { // while there are pending events
    XEvent ev;
    XNextEvent(display, &ev); // get next event

    // Check for window close event
    if (ev.type == ClientMessage &&
        (Atom)ev.xclient.data.l[0] == wmDeleteMessage) {
      return true;
    }

    // Redraw if requested
    if (ev.type == Expose) {
      redraw();
    }

    // Handle key presses
    if (ev.type == KeyPress) {
      KeySym key;
      char buf[8];
      int len = XLookupString(&ev.xkey, buf, sizeof(buf), &key, nullptr);

      if (key == XK_BackSpace && !inputBuffer.empty()) {
        inputBuffer.pop_back();
      } else if (key == XK_Return && !inputBuffer.empty()) {
        lineReady = true;
      } else if (len == 1 && buf[0] >= 32 && buf[0] <= 126 &&
                 inputBuffer.size() < maxInputSize) {
        inputBuffer += buf[0]; // only append if under limit
      }

      redraw();
    }
  }
  return false; // no close event
}

// Check if Enter was pressed and return input line
bool X11Window::pollLine(std::string &out) {
  if (!lineReady)
    return false; // nothing ready

  out = inputBuffer;   // copy input buffer
  inputBuffer.clear(); // clear buffer
  lineReady = false;   // reset flag
  redraw();            // redraw empty input line
  return true;
}
