#include <QApplication>
#include <unistd.h>
#include <iostream>

#include "mainwindow.h"
#include "mousebutton.h"

#include "cursormanagerfactory.h"
#include "networkmanager.h"
#include "unixipgetter.h"

using namespace std;


void treatData(NetworkManager *nm, CursorManager *cm)
{
    string cmd;
    while ((cmd=nm->getData()) != "") {
        if (cmd == "L") {
            cm->click(LEFT);
        } else if (cmd == "R") {
            cm->click(RIGHT);
        } else if (cmd == "M") {
            cm->click(MIDDLE);
        } else if (cmd == "U") {
            cm->click(WHUP);
        } else if (cmd == "D") {
            cm->click(WHDOWN);
        } else if (cmd[0] = 'W') {

            char *str = (char *)cmd.c_str();
            char * pch;
            pch = strtok (str," ");
            pch = strtok (NULL, " ");
            int x = atoi(pch);
            pch = strtok (NULL, " ");
            int y = atoi(pch);

            cm->moveRelative(x, y);

        }
    }
}


int main()
{
    CursorManager *cm = CursorManagerFactory::getCursorManager();
    UnixIPGetter ipGetter;
    NetworkManager nm;
    string *ip;
    cout << "getting ip" << endl;
    ip = ipGetter.getLocalIP();
    cout << "yolo" << endl;
    if (ip == nullptr)
    {
        std::cout << "no local ip found!" << std::endl;
        return 0;
    }


    std::cout << "using " << ip << std::endl;

    nm.createServer(1339);
    std::cout << "server created, waiting for connection" << std::endl;
    nm.connect();
    std::cout << "client connected!" << std::endl;

    treatData(&nm, cm);


    //CursorManager *cursor = CursorManagerFactory::getCursorManager();
    //cursor->moveCursorTo(50,15);
    //cursor->click(WHDOWN);

    return 0;

}




