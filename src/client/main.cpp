#include "main.hpp"

std::string website = "http://strongdoge.temp.swtest.ru";
std::string ip = "127.0.0.1";
int port = 5500;

std::string username = "user1";
std::string password = "user1";

MainClient *client = nullptr;

int PressAnyKey();

std::string FindArgumentInCommandLine(std::string argument) {
  std::string value = "";
  if (g_argc > 1) {
    for (int i = 1; i < g_argc; i += 2) {
      if (i + 1 < g_argc) {
        std::string arg = g_argv[i];
        if (arg == argument) {
          value = g_argv[i + 1];
          return value;
        }
      }
    }
  }
  return value;
}

void InitCommandLineArgs() {
  /*std::cout << FindArgumentInCommandLine("-username") << std::endl;
  std::cout << FindArgumentInCommandLine("-password") << std::endl;*/
}

void StartClient() {
  WSADATA wsaData;
  SOCKET sockfd;
  struct sockaddr_in server_addr;

  // Инициализация Winsock
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // Создание UDP сокета
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  // Заполнение структуры адреса сервера
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port); // Порт сервера
  server_addr.sin_addr.s_addr = inet_addr(ip.c_str()); // IP-адрес сервера

  const char *message = "Test, message!";

  // Отправка сообщения серверу
  sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

  char buffer[1024];

  // Ожидание ответа от сервера
  int server_len = sizeof(server_addr);
  int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
           (struct sockaddr *)&server_addr, &server_len);

  buffer[server_len] = '\0'; // Завершение строки
  std::cout << "Receive " << std::to_string(n) << " bytes "
            << buffer << ", from "
            << NetHelper::SockaddrToString((sockaddr *)&server_addr)
            << std::endl;

  Sleep(10);

  sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

  closesocket(sockfd); // Закрытие сокета
  WSACleanup();        // Очистка Winsock
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  g_argc = argc;
  g_argv = argv;

  InitCommandLineArgs();

  std::cout << "\tTest UDP Client" << std::endl;

  StartClient();

  /*client = new MainClient();
  client->Connect(ip, port);*/

  /*std::string response = WebRequest::Get(
      website, "func/test",
      "username=" + username + "; password=" + password + "; test=true");
  std::cout << response << std::endl;*/

  return PressAnyKey();
}

int PressAnyKey() {
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}