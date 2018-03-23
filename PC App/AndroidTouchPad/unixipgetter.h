#ifndef UNIXIPGETTER_H
#define UNIXIPGETTER_H

#include "ipgetter.h"



class UnixIPGetter : public IPGetter
{
public:
    UnixIPGetter();
    char* getLocalIP();

private:
    bool isLocal(char *ip);
};

#endif // UNIXIPGETTER_H
