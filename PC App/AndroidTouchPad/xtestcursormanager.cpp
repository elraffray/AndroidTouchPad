#include "xtestcursormanager.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

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
    XQueryPointer(dpy, RootWindow (dpy, 0),
                  &event.xbutton.root,
                  &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);
}

void XTestCursorManager::moveCursorTo(int x, int y)
{
    XTestFakeMotionEvent (dpy, 0, x, y, CurrentTime);
    XSync(dpy, 1);
}

void XTestCursorManager::moveRelative(int x, int y)
{
    updateCursor();
    cout << "X: " << event.xbutton.x_root << "Y: " << event.xbutton.y_root << endl;
    moveCursorTo(event.xbutton.x_root + x, event.xbutton.y_root + y);
}

void XTestCursorManager::click(MouseButton b)
{
    XTestFakeButtonEvent(dpy, b, True,  CurrentTime);
    XTestFakeButtonEvent(dpy, b, False,  CurrentTime);
    XFlush(dpy);
}
