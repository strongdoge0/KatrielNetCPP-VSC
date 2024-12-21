#include "MainServer.hpp"

bool MainServer::IsListening() { return _listening; }

bool MainServer::IsActive() { return true; }

void MainServer::Log(std::string message, LogType logType) {}

bool MainServer::Listen(int port) {
  _port = port;

  // Инициализация Winsock
  WSAStartup(MAKEWORD(2, 2), wsaData);

  // Создание UDP сокета
  _serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (_serverSocket == -1) {
    std::cout << "Listen error: unable to create socket" << std::endl;
    return false;
  }

  _serverAddr = new struct sockaddr_in();
  // Заполнение структуры адреса сервера
  _serverAddr->sin_family = AF_INET;
  _serverAddr->sin_addr.s_addr = INADDR_ANY; // Принимаем данные с любого IP
  _serverAddr->sin_port = htons(port); // Порт сервера

  // Привязка сокета к адресу
  if (bind(_serverSocket, (struct sockaddr *)_serverAddr,
           sizeof(_serverAddr)) == -1) {
    std::cout << "Listen error: unable to bind socket" << std::endl;
    return false;
  }

  _listening = true;
  listenCallbackThread =
      new std::thread(std::bind(&MainServer::ListenCallback, this));

  return true;
}

void MainServer::ListenCallback() {
  std::cout << "UDP server start listening at "
            << NetHelper::SockaddrToString(_serverAddr) << std::endl;
  while (_listening) {
    
  }
}

void MainServer::PollEvents() {}

void MainServer::Disconnect(ConnectionState connectionState) {}

void MainServer::Close() {}

void MainServer::Stop() {}
