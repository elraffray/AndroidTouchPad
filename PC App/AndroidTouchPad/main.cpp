#include <QApplication>
#include <unistd.h>

#include "mainwindow.h"
#include "mousebutton.h"

#include "cursormanagerfactory.h"
#include "networkmanager.h"
#include "unixipgetter.h"

int main()
{

    UnixIPGetter ipGetter;

    ipGetter.getLocalIP();
    //CursorManager *cursor = CursorManagerFactory::getCursorManager();
    //cursor->moveCursorTo(50,15);
    //cursor->click(WHDOWN);

    return 0;

}
