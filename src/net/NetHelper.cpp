#include "NetHelper.hpp"

std::string NetHelper::SockaddrToString(const sockaddr *addr) {

    // Буфер для хранения строкового представления адреса
    char address_string[22 /*INET_ADDRSTRLEN*/]; // Достаточно для IPv4
    DWORD address_string_length = sizeof(address_string);

    if (WSAAddressToStringA((LPSOCKADDR)addr, sizeof(sockaddr), NULL, address_string,
                            &address_string_length) != 0) {
      std::cerr << "Ошибка при преобразовании адреса: " << WSAGetLastError()
                << std::endl;
    }
    return std::string(address_string);
  }