#ifndef IPGETTERFACTORY_H
#define IPGETTERFACTORY_H

#include "ipgetter.h"

class IPgetterFactory
{
public:
    IPgetterFactory();
    static IPGetter *getIPgetter();
};

#endif // IPGETTERFACTORY_H
