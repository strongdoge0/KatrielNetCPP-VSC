#pragma once

#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

class ConnectionState{
    public:
    ConnectionState(struct sockaddr_in *client_addr);
    static const int bufferSize;
    
    private:
    struct sockaddr_in _addr;

};