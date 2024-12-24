#include "MainServer.hpp"

bool MainServer::IsListening() { return _listening; }

bool MainServer::IsActive() {
  if (_listening || _eventDispatcher.IsActive()) {
    return true;
  }
  return false;
}

void MainServer::Log(std::string message, LogType logType) {
  //"hh:mm:ss"
  std::time_t now = std::time(0);
  std::tm *localTime = std::localtime(&now);
  std::string prefix = "[" + std::to_string(localTime->tm_hour) + ":" +
                       std::to_string(localTime->tm_min) + ":" +
                       std::to_string(localTime->tm_sec) + "] " +
                       NetHelper::LogTypeToString((char)logType) + ": ";
  message = prefix + message;

  _eventDispatcher.Add([message, logType, this]() {
    if (OnLogCallback) {
      OnLogCallback(message, logType);
    }
  });
}

bool MainServer::Listen(int port) {
  _port = port;
#ifdef _WIN32
  // Инициализация Winsock
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

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
    socklen_t client_len = sizeof(client_addr);

    int bytesRead = recvfrom(_serverSocket, buffer, ConnectionState::bufferSize,
                             0, (struct sockaddr *)&client_addr, &client_len);

    if (bytesRead >= 0) {
      std::string data;
      data.assign(buffer, bytesRead);
      //Log("Test 1: " + NetHelper::SockaddrToString((sockaddr *)&client_addr));
      ReadCallback(&client_addr, data);

    } else {
      // -1 ни к чему
      /*Log("From " + NetHelper::SockaddrToString(&client_addr) + " received " +
          std::to_string(bytesRead) + " bytes");*/
    }
  }
}

ConnectionState *MainServer::FindConnectionState(struct sockaddr_in *addr) {
  for (int i = 0; i < _connectionStates.size(); i++) {
    if (NetHelper::СompareSockAddrIn(_connectionStates[i]->GetSockaddr(),
                                     addr)) {
      return _connectionStates[i];
    }
  }
  return nullptr;
}

void MainServer::ReadCallback(struct sockaddr_in *addr, std::string data) {

  MessageReader reader = MessageReader(data);
  // unsigned short size = reader.ReadUInt16();
  char id = reader.ReadChar();
  char flag = reader.ReadChar();

  // auto it = _connectionStates.find(addr);
  // if (it != _connectionStates.end()) {
  // if (_connectionStates.count(addr)) {
  /*if (false) {
    //  ConnectionState *connectionState = _connectionStates[addr];
    Log("Connection exists, nope");
  } else {
    ConnectionState *connectionState = new ConnectionState(addr);
    auto result = _connectionStates.insert({(sockaddr*)addr, connectionState});
    if (result.second) {
      // Log("New connection, added to map");
      _eventDispatcher.Add([connectionState, this]() {
        if (OnConnectCallback) {
          OnConnectCallback(connectionState);
        }
      });
    }else{
      Log("Connection exists, nope");
    }
  }*/

  ConnectionState *connectionState = FindConnectionState(addr);

  if (!connectionState) {
    /*ConnectionState **/connectionState = new ConnectionState(addr);
    _connectionStates.push_back(connectionState);
    // Log("New connection " + NetHelper::SockaddrToString(addr) + ", added");
    _eventDispatcher.Add([connectionState, this]() {
      if (OnConnectCallback) {
        OnConnectCallback(connectionState);
      }
    });
  } else {
    // Log("Connection " + NetHelper::SockaddrToString(addr) + " exists, nope");
  }
    /*int i = 0;
    for (const auto &element : _connectionStates) {
      i++;
      Log("Test 2: element " + std::to_string(i) + " " +
          NetHelper::SockaddrToString((sockaddr *)addr) + "|" +
          // NetHelper::SockaddrToString((sockaddr *)element.first) + "|" +
          // NetHelper::SockaddrToString((sockaddr
          // *)element.second->GetSockaddr()));
          NetHelper::SockaddrToString((sockaddr *)element->GetSockaddr()));
    }*/

    /*std::cout << "Log: From " << NetHelper::SockaddrToString((sockaddr *)addr)
              << " id " << (int)id << " flag "
              << NetHelper::MessageFlagToString(flag) //<< " type "
              //<< NetHelper::MessageTypeToString(type)
              << " received " << (int)data.length() << " bytes" << std::endl;*/

    Log("From " + NetHelper::SockaddrToString(addr) + " id " +
        std::to_string((int)id) + " flag " +
        NetHelper::MessageFlagToString(flag) + " received " +
        std::to_string((int)data.length()) + " bytes");

    /*std::cout << "Receive " << (int)data.length() << " bytes"
              << " flag " << NetHelper::MessageFlagToString(flag) << " type "
              << NetHelper::MessageTypeToString(type) << " from "
              << NetHelper::SockaddrToString((sockaddr *)addr) << std::endl;*/

    // auto conn = _connectionStates.find(addr);
    // if (conn != _connectionStates.end()) {
    //   ConnectionState *connectionState = conn->second;

    /*if ((MessageFlag)flag == MessageFlag::Accept) {

    }*/

    /*unsigned short type = reader.ReadUInt16();

    if ((MessageType)type == MessageType::Chat) {
      // const char *msg = reader.ReadCString();
      std::string str = reader.ReadString();
      // std::cout << " msg: " << msg << std::endl;
      // std::cout << " str: " << str << std::endl;
      Log("Message: " + str);
    }*/

   // without header
   std::string messageData = data.erase(0, ConnectionState::headerSize);

    _eventDispatcher.Add([connectionState, messageData, this]() {
      if (OnReceiveCallback) {
        OnReceiveCallback(connectionState, messageData);
      }
    });
  
}

std::string MainServer::GetHeader(unsigned short size, char id,
                                  MessageFlag flag) {
  MessageWriter writer = MessageWriter();
  // writer.Write(size);
  writer.Write(id);
  writer.Write((char)flag);
  return writer.GetData();
}

std::string MainServer::GetData(std::vector<std::any> vector) {
  MessageWriter writer = MessageWriter();
  for (int i = 0; i < vector.size(); i++) {
    if (vector[i].type() == typeid(bool)) {
      writer.Write(std::any_cast<bool>(vector[i]));
    } else if (vector[i].type() == typeid(char)) {
      writer.Write(std::any_cast<char>(vector[i]));
    } else if (vector[i].type() == typeid(short)) {
      writer.Write(std::any_cast<short>(vector[i]));
    } else if (vector[i].type() == typeid(unsigned short)) {
      writer.Write(std::any_cast<unsigned short>(vector[i]));
    } else if (vector[i].type() == typeid(int)) {
      writer.Write(std::any_cast<int>(vector[i]));
    } else if (vector[i].type() == typeid(unsigned int)) {
      writer.Write(std::any_cast<unsigned int>(vector[i]));
    } else if (vector[i].type() == typeid(float)) {
      writer.Write(std::any_cast<float>(vector[i]));
    } else if (vector[i].type() == typeid(const char *)) {
      writer.Write(std::any_cast<const char *>(vector[i]));
    } else if (vector[i].type() == typeid(std::string)) {
      writer.Write(std::any_cast<std::string>(vector[i]));
    }
  }
  return writer.GetData();
}

/*template <typename... T>
void MainServer::SendSingleMessageTo(ConnectionState *connectionState, char id,
                                   MessageFlag flag, T... args) {
  std::vector<std::any> vector;
  (vector.push_back(std::forward<T>(args)), ...);
  std::string data = GetData(vector);
  std::string header = GetHeader(data.length(), 0, flag);
  SendCallback(connectionState, header + data);
}*/

void MainServer::SendSingleMessageTo(ConnectionState *connectionState, char id,
                                     MessageFlag flag,
                                     std::vector<std::any> args) {
  // std::vector<std::any> vector;
  // vector.push_back(msg);
  //(vector.push_back(std::forward<T>(args)), ...);
  std::string data = GetData(args);
  std::string header = GetHeader(data.length(), 0, flag);
  SendCallback(connectionState, header + data);
}

// template <typename... T>
void MainServer::SendMessageTo(ConnectionState *connectionState,
                               MessageFlag flag, std::vector<std::any> args) {
  // std::vector<std::any> vector;
  //(vector.push_back(std::forward<T>(args)), ...);
  // for
  std::string data = GetData(args);
  std::string header = GetHeader(data.length(), 0, flag);
  SendCallback(connectionState, header + data);
}

void MainServer::SendCallback(ConnectionState *connectionState,
                              std::string messageData) {

  // std::cout << "data " << messageData << std::endl;

  struct sockaddr_in client_addr = *connectionState->GetSockaddr();

  // Отправка ответа клиенту обратно его же сообщения
  int s = sendto(_serverSocket, messageData.c_str(), messageData.length(), 0,
                 (struct sockaddr *)&client_addr, sizeof(client_addr));
  if (s > 0) {
    /*std::cout << "Sent " << std::to_string(s) << " bytes"
              << " to "
              << NetHelper::SockaddrToString(
                     (sockaddr *)connectionState->GetSockaddr())
              << std::endl;*/
    Log("Sent: " + std::to_string(s) + " bytes to " +
            NetHelper::SockaddrToString(
                (sockaddr *)connectionState->GetSockaddr()),
        LogType::Log);
  } else {
#ifdef _WIN32
    Log("SendCallback error: " + std::to_string(WSAGetLastError()),
        LogType::Error);
#else
    Log("SendCallback error", LogType::Error);
#endif
  }
}

void MainServer::PollEvents() { _eventDispatcher.Execute(); }

void MainServer::Disconnect(ConnectionState *connectionState) {
  //
}

void MainServer::Close() {
  _listening = false;
  Log("UDP server closed", LogType::Info);
//
#ifdef _WIN32
  closesocket(_serverSocket); // Закрытие сокета
  WSACleanup();               // Очистка Winsock
#elif __linux__
  close(_serverSocket);
#endif
}

void MainServer::Stop() { Close(); }
