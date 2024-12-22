#include "NetHelper.hpp"

std::string NetHelper::SockaddrToString(const sockaddr *addr) {
  // Буфер для хранения строкового представления адреса
  char address_string[22 /*INET_ADDRSTRLEN*/]; // Достаточно для IPv4
  DWORD address_string_length = sizeof(address_string);

  if (WSAAddressToStringA((LPSOCKADDR)addr, sizeof(sockaddr), NULL,
                          address_string, &address_string_length) != 0) {
    std::cout << "SockaddrToString error: code " << WSAGetLastError()
              << std::endl;
  }
  return std::string(address_string);
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