#include "xtestcursormanager.h"
#include <unistd.h>
#include <cstring>
#include <iostream>



XTestCursorManager::XTestCursorManager()
{
    int *revertTo;
    dpy = XOpenDisplay(0);
}

XTestCursorManager::~XTestCursorManager()
{
    XCloseDisplay(dpy);
}

void XTestCursorManager::updateCursor()
{
    XQueryPointer(dpy, RootWindow (dpy, 0), &event.xbutton.root,
                  &event.xbutton.window, &event.xbutton.x_root,
                  &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);
}

void XTestCursorManager::moveCursorTo(int x, int y)
{
    XTestFakeMotionEvent (dpy, 0, x, y, CurrentTime);
    XSync(dpy, 0);
}

void XTestCursorManager::click(MouseButton b)
{
    XTestFakeButtonEvent(dpy, b, True,  CurrentTime);
    XTestFakeButtonEvent(dpy, b, False,  CurrentTime);
    XFlush(dpy);
}
