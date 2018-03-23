#include "unixipgetter.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <vector>
#include <cstring>

using namespace std;

UnixIPGetter::UnixIPGetter()
{

}

//Return the computer's local IP
char *UnixIPGetter::getLocalIP()
{
    struct ifaddrs * ifAddrStruct=NULL;
        struct ifaddrs * ifa=NULL;
        void * tmpAddrPtr=NULL;

        getifaddrs(&ifAddrStruct);

        for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa ->ifa_addr->sa_family==AF_INET) { // check it is IP4
                // is a valid IP4 Address
                tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
                char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
                cout << ifa->ifa_name << ": " << addressBuffer << endl;
                if (isLocal(addressBuffer)) {
                    cout << "Found local address: " << addressBuffer << endl;
                    return addressBuffer;
                }
            }
            /*else if (ifa->ifa_addr->sa_family==AF_INET6) { // check it is IP6
                // is a valid IP6 Address
                tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
                char addressBuffer[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
                cout << ifa->ifa_name << ": " <<  addressBuffer << endl;
            }*/
        }
        cout << "end for" << endl;
        if (ifAddrStruct!=NULL)
            freeifaddrs(ifAddrStruct);//remember to free ifAddrStruct
        return nullptr;
}

//Checks if given IP is a local one
bool UnixIPGetter::isLocal(char * ip)
{
    char *tmp, *res;
    strcpy(tmp, ip);
    vector<char *> members;
    res= strtok(tmp,".");

    while (res != NULL)
    {
        members.push_back(res);
        res = strtok (NULL, ".");
    }

    if (atoi(members[0]) == 192 && atoi(members[1]) == 168) return true;
    return false;
}
