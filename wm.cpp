#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/cursorfont.h>

Display *dp;
Window root;

void error(char *msg) {
    puts(msg);
    exit(EXIT_FAILURE);
}

void grabKey(char *key, unsigned int mod) {
    KeySym sym = XStringToKeysym(key);
    KeyCode code = XKeysymToKeycode(dp, sym);
    XGrabKey(dp, code, mod, root, false, GrabModeAsync, GrabModeAsync);
    XSync(dp, false);
}

int main(void) {
    dp = XOpenDisplay(NULL);

    if (dp == NULL) {
        error("No display is opened dumbass");
    }

    root = DefaultRootWindow(dp);

    // Start getting inputs
    XSelectInput(dp, root, SubstructureRedirectMask | SubstructureNotifyMask);
    XSync(dp, 0);

    // Mouse stuff
    Cursor cursor = XCreateFontCursor(dp, XC_left_ptr);
    XDefineCursor(dp, root, cursor);
    XGrabButton(dp, Button1, 0, root, 0, ButtonPressMask, GrabModeSync, GrabModeAsync, NULL, NULL);
    XGrabButton(dp, Button2, 0, root, 0, ButtonPressMask, GrabModeSync, GrabModeAsync, NULL, NULL);
    XGrabButton(dp, Button3, 0, root, 0, ButtonPressMask, GrabModeSync, GrabModeAsync, NULL, NULL);
    XSync(dp, False);

    // Keyboard stuff
    grabKey("w", ShiftMask);

    // Event handler
    XEvent e;
    for (;;) {
        XNextEvent(dp, &e);
        switch (e.type) {
            default: {
                //puts("Unknown event");
                break;
            }
            case ButtonPress: {
                int type = e.xkey.type;
                int state = e.xkey.state;

                // Prevent X from freezing
                XAllowEvents(dp, ReplayPointer, CurrentTime);
                XSync(dp, 0);
                break;
            }
            case KeyPress: {
                char* key = XKeysymToString(XKeycodeToKeysym(dp, e.xkey.keycode, 0));
                int mod = e.xkey.state;

                break;
            }
        }
        XSync(dp, 0);
    }

    XCloseDisplay(dp);
}