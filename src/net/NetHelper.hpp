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

#include "KatrielNet.hpp"

class NetHelper {
public:
  static std::string SockaddrToString(const sockaddr *addr);
  static std::string SockaddrToString(struct sockaddr_in *addr_in);
  static std::string MessageFlagToString(char flag);
  static std::string MessageTypeToString(unsigned short type);
  static std::string LogTypeToString(char type);
};
