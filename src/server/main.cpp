#include "main.hpp"

std::string name = "Nexus";
std::string website = "http://strongdoge.temp.swtest.ru";
std::string ip = "127.0.0.1";
int port = 5500;

std::string username = "user1";
std::string password = "user1";

std::thread updateCallbackThread;
MainServer *server = nullptr;

//std::unordered_map<ConnectionState*, Player*> players;
std::vector<ConnectionState*> connectionStates;
std::mutex connectionStatesLock;

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

void Log(std::string message, LogType logType = LogType::Log){
  std::time_t now = std::time(0);
  std::tm *localTime = std::localtime(&now);
  std::string prefix = "[" + std::to_string(localTime->tm_hour) + ":" +
                       std::to_string(localTime->tm_min) + ":" +
                       std::to_string(localTime->tm_sec) + "] " +
                       NetHelper::LogTypeToString((char)logType) + ": ";
  std::cout << prefix + message << std::endl;
}

void OnLogCallback(std::string message, LogType logType) {
  std::cout << message << std::endl;
}

void OnConnectCallback(ConnectionState *connectionState) {
  std::unique_lock<std::mutex> guard(connectionStatesLock, std::try_to_lock);
  connectionStates.push_back(connectionState);
  
  //std::cout << "New connection " << NetHelper::SockaddrToString(connectionState->GetSockaddr()) << std::endl;
  Log("New connection " + NetHelper::SockaddrToString(connectionState->GetSockaddr()));
  //const char* msg = "Server: Welcome to the " + name.c_str() + ", this is a test message from server to new connection - for you!";
  std::string welcomeMessage = "Server: Welcome to the " + name + ", this is a welcome message from server to new connection - to you! Привет";
  server->SendSingleMessageTo(connectionState, (char)0, MessageFlag::Unreliable, {(unsigned short)MessageType::Chat, welcomeMessage});
  //server->SendMessageTo(connectionState, MessageFlag::Unreliable, {(unsigned short)MessageType::Chat, welcomeMessage});
}

void OnReceiveCallback(ConnectionState *connectionState, std::string data) {
  
  
  
  std::cout << "data: " << data << std::endl;
  
  /*MessageReader reader = MessageReader(*data);
  unsigned short type = reader.ReadUInt16();

  if ((MessageType)type == MessageType::Chat) {
    // const char *msg = reader.ReadCString();
    std::string str = reader.ReadString();
    // std::cout << " msg: " << msg << std::endl;
    // std::cout << " str: " << str << std::endl;
    Log("Message: " + str);
  }*/
  
}

void UpdateCallback() {
  while (server->IsActive()) {
    server->PollEvents();
#ifdef _WIN32    
    Sleep(100);
#else
    //sleep(100);
    usleep(100000); //100000 микросекунд = 100 мс
#endif
  }
  //std::cout << "UpdateCallback closed" << std::endl;
  Log("UpdateCallback closed");
}

void SendToAll(std::string message){
  std::unique_lock<std::mutex> guard(connectionStatesLock, std::try_to_lock);
  for (int i = 0; i < connectionStates.size(); i++){
    server->SendSingleMessageTo(connectionStates[i], 0, MessageFlag::Unreliable, {(unsigned short)MessageType::Chat, message});
  }
}

int main(int argc, char **argv) {
  g_argc = argc;
  g_argv = argv;

  InitCommandLineArgs();

  std::cout << "\tKatriel's UDP Server++" << std::endl;

  server = new MainServer();
  server->OnLogCallback = OnLogCallback;
  server->OnConnectCallback = OnConnectCallback;
  server->OnReceiveCallback = OnReceiveCallback;
  server->Listen(port);

  updateCallbackThread = std::thread(UpdateCallback);

  while (server->IsListening()) {
    std::string cmd;
    std::getline(std::cin, cmd);

    if (cmd == "q") {
      server->Stop();
    }else{
      SendToAll("Server:" + cmd);
    }
  }

  return PressAnyKey();
}

int PressAnyKey() {
  std::cout << "Press any key for exit" << std::endl;
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}