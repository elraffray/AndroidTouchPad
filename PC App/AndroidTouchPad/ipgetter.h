#ifndef IPGETTER_H
#define IPGETTER_H

#include <string>

class IPGetter
{
public:
    IPGetter() {}
    virtual ~IPGetter() {}

    virtual std::string *getLocalIP() = 0;
};

#endif // IPGETTER_H
