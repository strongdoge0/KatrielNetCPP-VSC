#pragma once

#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#include "KatrielNet.hpp"

class NetHelper {
public:
  static std::string SockaddrToString(const sockaddr *addr);
  static std::string SockaddrToString(struct sockaddr_in *addr_in);
  static std::string MessageFlagToString(char flag);
  static std::string MessageTypeToString(unsigned short type);
  static std::string LogTypeToString(char type);
};
