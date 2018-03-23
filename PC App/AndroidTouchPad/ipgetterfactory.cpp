#include "ipgetterfactory.h"
#include "defineos.h"

#ifdef OS_LINUX
    #include "unixipgetter.h"
#else

#endif

IPgetterFactory::IPgetterFactory()
{

}

IPGetter *IPgetterFactory::getIPgetter()
{
#ifdef OS_LINUX
    return new UnixIPGetter();
#else

#endif
}
