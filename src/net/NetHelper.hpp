#pragma once

#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

class NetHelper {
public:
  static std::string SockaddrToString(const sockaddr *addr);
  static std::string SockaddrToString(struct sockaddr_in *addr_in);
};
