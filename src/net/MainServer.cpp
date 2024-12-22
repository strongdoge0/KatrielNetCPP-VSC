#include "MainServer.hpp"

bool MainServer::IsListening() { return _listening; }

bool MainServer::IsActive() {
  if (_listening || _eventDispatcher.IsActive()) {
    return true;
  }
  return false;
}

void MainServer::Log(std::string message, LogType logType) {
  /*std::lock_guard<std::mutex> guard(_eventsLock);
  _events.push_back(
      [message]() { std::cout << "Action Log: " << message << std::endl; });*/
  /*_eventDispatcher.Add(
      [message]() { std::cout << "Action Log: " << message << std::endl; });*/
  _eventDispatcher.Add([message, logType, this]() {
    if (OnLogCallback) {
      OnLogCallback(message, logType);
    }
  });
}

bool MainServer::Listen(int port) {
  _port = port;

  // Инициализация Winsock
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // Создание UDP сокета
  _serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (_serverSocket == -1) {
    // std::cout << "Listen error: unable to create socket" << std::endl;
    Log("Listen error: unable to create socket", LogType::Error);
    return false;
  }

  //_serverAddr = new struct sockaddr_in();
  memset(&_serverAddr, 0, sizeof(_serverAddr));
  // Заполнение структуры адреса сервера
  _serverAddr.sin_family = AF_INET;
  _serverAddr.sin_addr.s_addr = INADDR_ANY; // Принимаем данные с любого IP
  _serverAddr.sin_port = htons(port); // Порт сервера

  // Привязка сокета к адресу
  if (bind(_serverSocket, (struct sockaddr *)&_serverAddr,
           sizeof(_serverAddr)) == -1) {
    Log("Listen error: unable to bind socket", LogType::Error);
    return false;
  }

  _listening = true;
  listenCallbackThread =
      std::thread(std::bind(&MainServer::ListenCallback, this));

  return true;
}

void MainServer::ListenCallback() {
  // std::cout << "UDP server start listening at "
  //           << NetHelper::SockaddrToString(&_serverAddr) << std::endl;
  Log("UDP server start listening at " +
          NetHelper::SockaddrToString(&_serverAddr),
      LogType::Info);
  while (_listening) {
    struct sockaddr_in client_addr;
    char *buffer = new char[ConnectionState::bufferSize];
    int client_len = sizeof(client_addr);

    int bytesRead = recvfrom(_serverSocket, buffer, ConnectionState::bufferSize,
                             0, (struct sockaddr *)&client_addr, &client_len);

    if (bytesRead >= 0) {
      std::string data;
      data.assign(buffer, bytesRead);

      ReadCallback(&client_addr, data);

    } else {
      /*std::cout << "Receive " << std::to_string(bytesRead) << " bytes from "
                << NetHelper::SockaddrToString((sockaddr *)&client_addr)
                << std::endl;*/
      Log("Log: From " + NetHelper::SockaddrToString(&_serverAddr) +
          " received " + std::to_string(bytesRead) + " bytes");
    }
  }
}

void MainServer::ReadCallback(sockaddr_in *addr, std::string data) {

  MessageReader reader = MessageReader(data);
  unsigned short size = reader.ReadUInt16();
  char id = reader.ReadChar();
  char flag = reader.ReadChar();

  /*std::cout << "Log: From " << NetHelper::SockaddrToString((sockaddr *)addr)
            << " id " << (int)id << " flag "
            << NetHelper::MessageFlagToString(flag) //<< " type "
            //<< NetHelper::MessageTypeToString(type)
            << " received " << (int)data.length() << " bytes" << std::endl;*/

  Log("Log: From " + NetHelper::SockaddrToString(&_serverAddr) + " id " +
      std::to_string((int)id) + " flag " +
      NetHelper::MessageFlagToString(flag) + " received " +
      std::to_string((int)data.length()) + " bytes");

  /*std::cout << "Receive " << (int)data.length() << " bytes"
            << " flag " << NetHelper::MessageFlagToString(flag) << " type "
            << NetHelper::MessageTypeToString(type) << " from "
            << NetHelper::SockaddrToString((sockaddr *)addr) << std::endl;*/

  auto conn = _connectionStates.find(addr);
  if (conn != _connectionStates.end()) {
    ConnectionState *connectionState = conn->second;
    Log("Connection exists, nope");
  } else {
    ConnectionState *connectionState = new ConnectionState(addr);
    _connectionStates[addr] = connectionState;
    Log("New connection, added to map");
  }

  /*if ((MessageFlag)flag == MessageFlag::Accept) {
    
  }*/

  unsigned short type = reader.ReadUInt16();

  if ((MessageType)type == MessageType::Chat) {
    // const char *msg = reader.ReadCString();
    std::string str = reader.ReadString();
    // std::cout << " msg: " << msg << std::endl;
    // std::cout << " str: " << str << std::endl;
    Log("Message: " + str);
  }
}

void MainServer::PollEvents() { _eventDispatcher.Execute(); }

void MainServer::Disconnect(ConnectionState connectionState) {
  //
}

void MainServer::Close() {
  _listening = false;
  Log("UDP server closed", LogType::Info);
  //
}

void MainServer::Stop() { Close(); }
