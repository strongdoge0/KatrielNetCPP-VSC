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
      if (i+1 < g_argc) {
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

int main(int argc, char **argv) {
  g_argc = argc;
  g_argv = argv;

  std::cout << "\tTest UDP Client" << std::endl;

  std::cout << FindArgumentInCommandLine("-username") << std::endl;
  std::cout << FindArgumentInCommandLine("-password") << std::endl;

  client = new MainClient();
  client->Connect(ip, port);

  std::string response = WebRequest::Get(
      website, "func/test",
      "username=" + username + "; password=" + password + "; test=true");
  std::cout << response << std::endl;

  return PressAnyKey();
}

int PressAnyKey() {
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}