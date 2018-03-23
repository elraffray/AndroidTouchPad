#include "cursormanagerfactory.h"
#include "defineos.h"

#ifdef OS_LINUX
    #include "xtestcursormanager.h"
#else

#endif

class XTestCursorManager;

CursorManagerFactory::CursorManagerFactory()
{

}

CursorManager *CursorManagerFactory::getCursorManager()
{
    #ifdef OS_LINUX
        return new XTestCursorManager();
    #else

    #endif
}
