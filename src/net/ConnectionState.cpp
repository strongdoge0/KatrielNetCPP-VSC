#include "ConnectionState.hpp";

ConnectionState::ConnectionState(const sockaddr *addr){
    _addr = addr;
}