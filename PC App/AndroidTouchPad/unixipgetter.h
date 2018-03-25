#ifndef UNIXIPGETTER_H
#define UNIXIPGETTER_H

#include <string>
#include "ipgetter.h"



class UnixIPGetter : public IPGetter
{
public:
    UnixIPGetter();
    std::string *getLocalIP();

private:
    bool isLocal(char *ip);
};

#endif // UNIXIPGETTER_H
