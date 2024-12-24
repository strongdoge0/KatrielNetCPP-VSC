#pragma once

#include <iostream>
#include <string>

#ifdef _WIN32 // для Windows
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#elif __linux__ // для Linux
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#else
// неизвестная ОС
#endif

#include "KatrielNet.hpp"

class NetHelper {
public:
  static bool СompareSockAddrIn(const sockaddr_in *addr1,
                                const sockaddr_in *addr2);
  static std::string SockaddrToString(const sockaddr *addr);
  static std::string SockaddrToString(struct sockaddr_in *addr_in);
  static std::string MessageFlagToString(char flag);
  static std::string MessageTypeToString(unsigned short type);
  static std::string LogTypeToString(char type);
};
