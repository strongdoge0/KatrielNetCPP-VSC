#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32 // для Windows
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#elif __linux__ // для Linux
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
// неизвестная ОС
#endif

class ConnectionState{
    public:
    ConnectionState(struct sockaddr_in *client_addr);
    static const int bufferSize;
    static const int headerSize;
    struct sockaddr_in *GetSockaddr();
    
    private:
    struct sockaddr_in _addr;

};