#include "ConnectionState.hpp"

const int ConnectionState::bufferSize = 1024;
const int ConnectionState::headerSize = 2; // id 1 byte, flag 1 byte

ConnectionState::ConnectionState(struct sockaddr_in *addr){
    _addr = *addr;
}

struct sockaddr_in *ConnectionState::GetSockaddr(){
    return &_addr;
}