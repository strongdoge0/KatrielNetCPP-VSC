#include "main.hpp"

std::string website = "http://strongdoge.temp.swtest.ru";
std::string ip = "127.0.0.1";
int port = 5500;

std::string username = "user1";
std::string password = "user1";

MainServer *server = nullptr;

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
  // nope
}

/*void sockaddr_to_string(const sockaddr* addr, char* buffer, DWORD*
buffer_length) { if (WSAAddressToStringA((LPSOCKADDR)addr, sizeof(sockaddr),
NULL, buffer, buffer_length) != 0) { std::cerr << "Ошибка при преобразовании
адреса: " << WSAGetLastError() << std::endl;
    }
}*/

void StartServer() {
  WSADATA wsaData;
  SOCKET sockfd;
  struct sockaddr_in server_addr, client_addr;
  //char buffer[1024];
  int bufferSize = 1024; // + 1;
  char *buffer = new char[bufferSize];
  int client_len = sizeof(client_addr);

  // Инициализация Winsock
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // Создание UDP сокета
  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  // Заполнение структуры адреса сервера
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY; // Принимаем данные с любого IP
  server_addr.sin_port = htons(port); // Порт сервера

  // Привязка сокета к адресу
  bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  std::cout << "UDP server start on port " << std::to_string(port) << std::endl;

  while (true) {
    // Прием данных от клиента
    //int r = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
    //                 (struct sockaddr *)&client_addr, &client_len);
    //buffer[r] = '\0'; // Завершение строки

     int r = recvfrom(sockfd, buffer, bufferSize, 0,
                      (struct sockaddr *)&client_addr, &client_len);
     //buffer[r] = '\0'; // Завершение строки, ничего не даст, так как данные бинарные

    if (r >= 0) {

      std::string data;
      data.assign(buffer, r);

      for (int i = 0; i < r; i++) {
        //data.push_back(buffer[i]);
        std::cout << "byte " << std::to_string(i) << " = " << buffer[i] << "|"
                  << +buffer[i] << std::endl;
      }
      std::cout << std::endl;
      //MessageReader reader = MessageReader(std::string(buffer));  // не будет работать, так как бинарные данные нельзя записать в текст
      MessageReader reader = MessageReader(data);
      
      std::string testData = reader.GetData();

      for (int i = 0; i < testData.length(); i++) {
        std::cout << "data " << std::to_string(i) << " = " << testData[i] << "|"
                  << +testData[i] << std::endl;
      }
      std::cout << std::endl;
      char flag = reader.ReadChar();
      unsigned char type = reader.ReadUInt16();
      /*std::cout << "Receive " << std::to_string(r) << " bytes"
                << " message: " << buffer
                << " from " << NetHelper::SockaddrToString((sockaddr
         *)&client_addr)
                << std::endl;*/

      std::cout << "Receive " << std::to_string(r) << " bytes"
                << " flag " << (int)flag << " type " << (int)type << " from "
                << NetHelper::SockaddrToString((sockaddr *)&client_addr)
                << std::endl;

      if ((MessageType)type == MessageType::Chat) {
        const char *msg = reader.ReadCString();
        std::string str = reader.ReadString();
        std::cout << " msg: " << msg << std::endl;
        std::cout << " str: " << str << std::endl;
        std::cout << " data: " << buffer << std::endl;
      }

      // Отправка ответа клиенту обратно его же сообщения
      int s = sendto(sockfd, buffer, r, 0, (struct sockaddr *)&client_addr,
                     client_len);
      std::cout << "Send " << std::to_string(s) << " bytes"
                << " to "
                << NetHelper::SockaddrToString((sockaddr *)&client_addr)
                << std::endl;
    }

    Sleep(10);
  }

  closesocket(sockfd); // Закрытие сокета
  WSACleanup();        // Очистка Winsock
}

int main(int argc, char **argv) {
  // setlocale(LC_ALL, "ru_RU.UTF-8");
  // SetConsoleCP(1251); // Установка кодовой страницы для ввода
  // SetConsoleOutputCP(1251); // Установка кодовой страницы для вывода
  g_argc = argc;
  g_argv = argv;

  InitCommandLineArgs();

  std::cout << "\tTest UDP Server" << std::endl;

  StartServer();

  /*server = new MainClient();
  server->Connect(ip, port);*/

  return PressAnyKey();
}

int PressAnyKey() {
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}