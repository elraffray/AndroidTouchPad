#ifndef XTESTCURSORMANAGER_H
#define XTESTCURSORMANAGER_H

#include <X11/extensions/XTest.h>
#include "cursormanager.h"



class XTestCursorManager : public CursorManager
{
public:
    XTestCursorManager();
    ~XTestCursorManager();
    Display *getDisplay() { return dpy; }

    void moveCursorTo(int x, int y);
    void moveRelative (int x, int y);
    void click(MouseButton b);
    void updateCursor();

private:
    Display *dpy;
    XEvent event;
};

#endif // XLIBMANAGER_H
