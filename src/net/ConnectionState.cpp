#include "ConnectionState.hpp";

const int ConnectionState::bufferSize = 1024;

ConnectionState::ConnectionState(struct sockaddr_in *addr){
    _addr = *addr;
}