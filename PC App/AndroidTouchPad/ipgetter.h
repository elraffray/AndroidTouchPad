#ifndef IPGETTER_H
#define IPGETTER_H


class IPGetter
{
public:
    IPGetter() {}
    virtual ~IPGetter() {}

    virtual char* getLocalIP() = 0;
};

#endif // IPGETTER_H
