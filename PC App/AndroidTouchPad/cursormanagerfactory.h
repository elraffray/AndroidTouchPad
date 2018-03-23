#ifndef CURSORMANAGERFACTORY_H
#define CURSORMANAGERFACTORY_H

#include "cursormanager.h"



class CursorManagerFactory
{
public:
    CursorManagerFactory();
    static CursorManager *getCursorManager();
};

#endif // CURSORMANAGERFACTORY_H
