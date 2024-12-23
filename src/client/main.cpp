#include "main.hpp"

std::string website = "http://strongdoge.temp.swtest.ru";
std::string ip = "127.0.0.1";
//std::string ip = "188.130.251.54";
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

std::string GetHeader(unsigned short size, char id, MessageFlag flag){
  MessageWriter writer = MessageWriter();
  //writer.Write(size);
  writer.Write(id);
  writer.Write((char)flag);
  return writer.GetData();
}

std::string GetData(std::vector<std::any> vector) {
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
      // std::cout << std::any_cast<const char *>(vector[i]) << std::endl;
    } else if (vector[i].type() == typeid(std::string)) {
      writer.Write(std::any_cast<std::string>(vector[i]));
      // std::cout << std::any_cast<std::string>(vector[i]) << std::endl;
    }
  }
  return writer.GetData();
}
template <typename... T>
std::string SendMessageTo(MessageFlag flag, T... args) {
  // std::cout << "flag " << (int)flag << ": "; // std::endl;
  std::vector<std::any> vector;
  //unsigned short size = 0;
  //vector.push_back((unsigned short)size);
  //char id = 0;
  //vector.push_back((char)id);
  //vector.push_back((char)flag);
  (vector.push_back(std::forward<T>(args)), ...);
  std::string data = GetData(vector);

  std::string header = GetHeader(data.length(), 0, flag);

  // Test
  /*try {

    for (int i = 0; i < data.length(); i++) {
      std::cout << "byte " << std::to_string(i) << " = " << data[i] << "|"
                << +data[i] << std::endl;
    }
    std::cout << std::endl;
    MessageReader reader = MessageReader(data);

    std::string testData = reader.GetData();

    for (int i = 0; i < testData.length(); i++) {
      std::cout << "data " << std::to_string(i) << " = " << testData[i] << "|"
                << +testData[i] << std::endl;
    }
    std::cout << std::endl;
    char _flag = reader.ReadChar();
    unsigned short type = reader.ReadUInt16();
    const char *msg = reader.ReadCString();
    std::string str = reader.ReadString();

    std::cout << "flag " << (int)_flag << std::endl;
    std::cout << "type " << type << std::endl;
    std::cout << "msg " << msg << std::endl;
    std::cout << "str " << msg << std::endl;

    // std::cout << data << std::endl;
  } catch (std::exception e) {
    std::cout << e.what() << std::endl;
  }*/
  return header+data;
}

void StartClient() {
  #ifdef _WIN32
  WSADATA wsaData;
  #endif
  SOCKET sockfd;
  struct sockaddr_in server_addr;
#ifdef _WIN32
  // Инициализация Winsock
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
  // Создание UDP сокета
  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  // Заполнение структуры адреса сервера
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port); // Порт сервера
  server_addr.sin_addr.s_addr = inet_addr(ip.c_str()); // IP-адрес сервера

  std::cout << "Experimental UDP client start"<< std::endl;


  while (true) {
    std::string message;
    std::getline(std::cin, message);

    if (message == "q"){
      break;
    }

    std::string msg = SendMessageTo(MessageFlag::Unreliable,
                                    (unsigned short)MessageType::Chat,
                                    message.c_str(), message);

    int s = sendto(sockfd, msg.c_str(), msg.length(), 0,
                   (struct sockaddr *)&server_addr, sizeof(server_addr));

    // int s = sendto(sockfd, message.c_str(), message.length()
    // /*strlen(message)*/, 0,
    //            (struct sockaddr *)&server_addr, sizeof(server_addr));

    std::cout << "Send " << std::to_string(s) << " bytes " << message << " to "
              << NetHelper::SockaddrToString((sockaddr *)&server_addr)
              << std::endl;

    //continue;

    // char buffer[1024];
    int bufferSize = 1024; // + 1;
    char *buffer = new char[bufferSize];

    // Ожидание ответа от сервера
    socklen_t server_len = sizeof(server_addr);
    // int r = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
    //                  (struct sockaddr *)&server_addr, &server_len);
    int r = recvfrom(sockfd, buffer, bufferSize, 0,
                     (struct sockaddr *)&server_addr, &server_len);
    // buffer[r] = '\0'; // Завершение строки, ничего не даст, так как данные
    // бинарные

    if (r >= 0) {
      /*std::cout << "Receive "
                << std::to_string(r)
                << " bytes"
                << " message: " << buffer << " from "
                << NetHelper::SockaddrToString((sockaddr *)&server_addr)
                << std::endl;*/

      std::string data;
      data.assign(buffer, r);

      /*for (int i = 0; i < r; i++) {
        std::cout << "byte " << std::to_string(i) << " = " << buffer[i] << "|"
                  << +buffer[i] << std::endl;
      }
      std::cout << std::endl;*/

      // MessageReader reader = MessageReader(std::string(buffer)); // не будет
      // работать, так как бинарные данные нельзя записать в текст
      MessageReader reader = MessageReader(data);

      std::string testData = reader.GetData();

      /*for (int i = 0; i < testData.length(); i++) {
        std::cout << "data " << std::to_string(i) << " = " << testData[i] << "|"
                  << +testData[i] << std::endl;
      }
      std::cout << std::endl;*/
      //unsigned char size = reader.ReadUInt16();
      char id = reader.ReadChar();
      char flag = reader.ReadChar();
      unsigned char type = reader.ReadUInt16();
      /*std::cout << "Receive " << std::to_string(n) << " bytes"
                << " message: " << buffer
                << " from " << NetHelper::SockaddrToString((sockaddr
         *)&client_addr)
                << std::endl;*/

      std::cout << "Receive " << std::to_string(r) << " bytes"
                << " flag " << (int)flag << " type " << (int)type << " from "
                << NetHelper::SockaddrToString((sockaddr *)&server_addr)
                << std::endl;

      if ((MessageType)type == MessageType::Chat) {
        const char *msg = reader.ReadCString();
        //std::string str = reader.ReadString();
        std::cout << " msg: " << msg << std::endl;
        //std::cout << " str: " << str << std::endl;
        //std::cout << " data: " << buffer << std::endl;
      }
    }

    #ifdef _WIN32    
    Sleep(100);
#else
    //sleep(100);
    usleep(100000); //100000 микросекунд = 100 мс
#endif
  }
  
  std::cout << "UDP client closed"<< std::endl;
  
#ifdef _WIN32
  closesocket(sockfd); // Закрытие сокета
  WSACleanup();        // Очистка Winsock
  #elif __linux__
  close(sockfd);  
  #endif
}

void Test() {

  // Пример данных для записи
  int number = 42;
  const char *text = "Hello";
  std::string str = "world!";

  /*
  // Создаем строковый поток для записи
  std::ostringstream oss(std::ios::binary);

  // Записываем данные в поток
  oss.write(reinterpret_cast<const char *>(&number),
            sizeof(number)); // Запись целого числа
  //oss << number;

  int *size_t* length = strlen(text); // Длина строки
  oss << length;
  //oss.write(reinterpret_cast<const char *>(&length),
  //          sizeof(length)); // Запись длины строки
  oss.write(text, length);   // Запись самой строки
  //oss << text;


  //length = str.length(); // Длина строки
  //oss.write(reinterpret_cast<const char *>(&length),
  //          sizeof(length));      // Запись длины строки
  //oss.write(str.c_str(), length); // Запись самой строки
  oss << str;

  // Получаем строку из потока
  std::string binaryData = oss.str();
  */

  MessageWriter writer = MessageWriter();
  writer.Write(number);
  writer.Write(text);
  writer.Write(str);

  std::string binaryData = writer.GetData();

  int readNumber;
  char readText[255]; // Предполагаем, что текст не превышает 255 символов
  //  const char* readText;
  std::string readStr;

  /*
  // Теперь читаем данные из строки
  std::istringstream iss(binaryData, std::ios::binary);

  // Читаем данные из потока
  iss.read(reinterpret_cast<char *>(&readNumber),
           sizeof(readNumber)); // Чтение целого числа
  // iss >> readNumber;

  char *size_t* readLength;
  iss >> readLength;
  // iss.read(reinterpret_cast<char*>(&readLength), sizeof(readLength)); //
  // Чтение длины строки
  iss.read(readText, readLength); // Чтение самой строки
  // iss >> readText;
  readText[readLength] = '\0'; // Завершаем строку нулевым символом

  iss.read(reinterpret_cast<char*>(&readLength), sizeof(readLength)); //
  // Чтение длины строки
  //iss >> readStr;
  char readCStr[readLength];
  iss.read(readCStr, readLength);

  readStr = std::string(readCStr);
  */

  MessageReader reader = MessageReader(binaryData);
  readNumber = reader.ReadInt32();
  const char *_readText = reader.ReadCString();

  /*for (int i = 0; i < sizeof(_readText) / sizeof(char); i++) {
    readText[i] = _readText[i];
  }*/
  strcpy(readText, _readText);

  readStr = reader.ReadString();

  // Выводим прочитанные данные
  std::cout << "number: " << readNumber << std::endl;
  std::cout << "_text: " << _readText << std::endl;
  std::cout << "text: " << readText << std::endl;
  std::cout << "str from text: " << std::string(readText) << std::endl;
  std::cout << "str: " << readStr << std::endl;
}

int main(int argc, char **argv) {
  // setlocale(LC_ALL, "ru_RU.UTF-8");
  // SetConsoleCP(1251); // Установка кодовой страницы для ввода
  // SetConsoleOutputCP(1251); // Установка кодовой страницы для вывода
  g_argc = argc;
  g_argv = argv;

  InitCommandLineArgs();

  std::cout << "\tKatriel's UDP Client++" << std::endl;

  // Test();

  /*SendMessage(MessageFlag::None);
  SendMessage(MessageFlag::Unreliable, 0);
  SendMessage(MessageFlag::Reliable, 0, "Abc");
  SendMessage(MessageFlag::Secure, 0, "Abc", 'b');
  SendMessage(MessageFlag::Success, 0, "Abc", 'b', 9.9f);*/

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
  std::cout << "Press any key for exit" << std::endl;
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}