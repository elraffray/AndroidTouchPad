#include "networkmanager.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <vector>

using namespace std;

NetworkManager::NetworkManager()
{

}

void NetworkManager::connect()
{
    if ((childSocket = accept(serverSocket, &srcAddr, &srcAddrLength))<0)
    {
        perror("accept");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

void NetworkManager::closeServer()
{
    close(childSocket);
    close(serverSocket);
}

string NetworkManager::getData()
{
    ret=recv(childSocket, data, DATA_MAX_LENGTH-1,0);
    if (ret < 0) {
        return "";
    }
    cout << "data is " << ret << " long" << endl;
    data[ret] = '\0';

    string s(data, ret);

    cout << "received" << s << endl;

    return s;
}



void NetworkManager::createServer(int port)
{
    int opt=1;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
       perror("ERROR opening socket");

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    if (listen(serverSocket, 1))
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server has started successfully. Info:" << endl;
    cout << "Port Number Listening to: " <<  port << endl;

    /*valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");*/
}



