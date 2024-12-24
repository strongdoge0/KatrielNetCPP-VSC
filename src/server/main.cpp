#include "main.hpp"

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

void OnLogCallback(std::string message, LogType logType) {
  std::cout << message << std::endl;
}

void OnConnectCallback(ConnectionState *connectionState) {
  std::unique_lock<std::mutex> guard(connectionStatesLock, std::try_to_lock);
  connectionStates.push_back(connectionState);
  
  std::cout << "New connection " << NetHelper::SockaddrToString(connectionState->GetSockaddr()) << std::endl;
  const char* msg = "Server: Welcome, this is a test message from server to new connection - for you!";
  server->SendSingleMessageTo(connectionState, (char)0, MessageFlag::Unreliable, {(unsigned short)MessageType::Chat, msg});
  //server->SendMessageTo(connectionState, MessageFlag::Unreliable, {(unsigned short)MessageType::Chat, msg});
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
  std::cout << "UpdateCallback closed" << std::endl;
}

void SendToAll(std::string message){
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