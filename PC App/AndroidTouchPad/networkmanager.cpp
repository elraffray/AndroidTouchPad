#include "networkmanager.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

using namespace std;

NetworkManager::NetworkManager()
{

}

void NetworkManager::connect()
{

    if ((childSocket = accept(serverSocket, &clientSocket, &clientNameLength))<0)
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
    if (listen(serverSocket, 3) < 0)
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



