#ifndef NETWORKMANAGER_H
#define NETWWORKMANAGER_H

#include <netinet/in.h>
#include <string>



class NetworkManager
{
public:
    NetworkManager();
    void createServer(int port);
    void connect();
    void closeServer();

private:
    struct sockaddr_in address;
    struct sockaddr clientSocket = {0};
    socklen_t clientNameLength = sizeof(clientSocket);
    int addrlen = sizeof(address), serverSocket, childSocket;
};

#endif // NETWORKMANAGER_H
