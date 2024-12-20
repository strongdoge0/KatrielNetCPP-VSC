#pragma once

#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

class ConnectionState{
    public:
    ConnectionState(const sockaddr *client_addr);
    
    private:
    const sockaddr *_addr;
    
};