#ifndef CURSORMANAGER_H
#define CURSORMANAGER_H

#include "mousebutton.h"



class CursorManager
{
public:
    virtual void moveCursorTo(int x, int y) = 0;
    virtual void moveRelative(int x, int y) = 0;
    virtual void click(MouseButton b) = 0;

    virtual ~CursorManager() {}
};

#endif // CURSORMANAGER_H
