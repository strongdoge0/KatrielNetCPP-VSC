#include "NetHelper.hpp"

std::string NetHelper::SockaddrToString(const sockaddr *addr) {
  #ifdef _WIN32
    // Буфер для хранения строкового представления адреса
  char address_string[46 /*22*/ /*INET_ADDRSTRLEN*/]; // Достаточно для IPv4
  DWORD address_string_length = sizeof(address_string);
  if (WSAAddressToStringA((LPSOCKADDR)addr, sizeof(sockaddr), NULL,
                          address_string, &address_string_length) != 0) {
    std::cout << "SockaddrToString error: code " << WSAGetLastError()
              << std::endl;
  }
    return std::string(address_string);
  #elif __linux__
    char ipstr[INET6_ADDRSTRLEN]; // Достаточно для хранения IPv6 адреса
    unsigned short port;
    switch (addr->sa_family) {
        case AF_INET: {
            // Преобразование IPv4
            struct sockaddr_in *s = (struct sockaddr_in *)addr;
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof(ipstr));
            port = ntohs(s->sin_port);
            break;
        }
        case AF_INET6: {
            // Преобразование IPv6
            struct sockaddr_in6 *s = (struct sockaddr_in6 *)addr;
            inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof(ipstr));
            port = ntohs(s->sin6_port);
            break;
        }
        default:
            return "Unknown address family";
    }
    return std::string(ipstr) + ":" + std::to_string(port);
  #endif
}

std::string NetHelper::SockaddrToString(struct sockaddr_in *addr_in) {
  return SockaddrToString((sockaddr *)addr_in);
}

std::string NetHelper::MessageFlagToString(char flag) {
  std::string result = std::to_string((int)flag);
  if ((MessageFlag)flag == MessageFlag::None) {
    result = "None";
  } else if ((MessageFlag)flag == MessageFlag::Unreliable) {
    result = "Unreliable";
  } else if ((MessageFlag)flag == MessageFlag::Reliable) {
    result = "Reliable";
  } else if ((MessageFlag)flag == MessageFlag::Secure) {
    result = "Secure";
  } else if ((MessageFlag)flag == MessageFlag::Fail) {
    result = "Fail";
  } else if ((MessageFlag)flag == MessageFlag::Accept) {
    result = "Accept";
  } else if ((MessageFlag)flag == MessageFlag::Success) {
    result = "Success";
  }
  return result;
}

std::string NetHelper::MessageTypeToString(unsigned short type) {
  std::string result = std::to_string((int)type);
  if ((MessageType)type == MessageType::None) {
    result = "None";
  } else if ((MessageType)type == MessageType::Chat) {
    result = "Chat";
  }
  return result;
}

std::string NetHelper::LogTypeToString(char type) {
  std::string result = std::to_string((int)type);
  if ((LogType)type == LogType::Log) {
    result = "Log";
  } else if ((LogType)type == LogType::Info) {
    result = "Info";
  } else if ((LogType)type == LogType::Warning) {
    result = "Warning";
  } else if ((LogType)type == LogType::Error) {
    result = "Error";
  }
  return result;
}