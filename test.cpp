#include <X11/Xlib.h>
#include <unistd.h>

main() {
    Display *dp = XOpenDisplay(0);

    int black = BlackPixel(dp, DefaultScreen(dp));
    int white = WhitePixel(dp, DefaultScreen(dp));

    Window w = XCreateSimpleWindow(dp, DefaultRootWindow(dp), 0, 0, 200, 100, 0, black, black);

    XSelectInput(dp, w, StructureNotifyMask);

    XMapWindow(dp, w);

    GC gc = XCreateGC(dp, w, 0, 0);

    XSetForeground(dp, gc, white);

    for (;;) {
        XEvent e;
        XNextEvent(dp, &e);
        if (e.type == MapNotify) {
            break;
        }
    }

    XDrawLine(dp, w, gc, 10, 60, 180, 20);

    XFlush(dp);

    sleep(10);
}