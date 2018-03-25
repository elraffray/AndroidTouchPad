#ifndef NETWORKMANAGER_H
#define NETWWORKMANAGER_H

#include <netinet/in.h>
#include <string>

#define DATA_MAX_LENGTH 1024

class NetworkManager
{
public:
    NetworkManager();
    void createServer(int port);
    void connect();
    void closeServer();
    std::string getData();

private:
    struct sockaddr_in address;
    struct sockaddr srcAddr = {0};
    socklen_t srcAddrLength = sizeof(srcAddr);
    int addrlen = sizeof(address), serverSocket, childSocket, ret;

    char data[DATA_MAX_LENGTH];

};

#endif // NETWORKMANAGER_H
