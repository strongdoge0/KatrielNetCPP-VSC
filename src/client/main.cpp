#include "main.hpp"

std::string website = "http://strongdoge.temp.swtest.ru";
std::string ip = "127.0.0.1";
int port = 5500;

MainClient* client = nullptr;

int PressAnyKey();

int main(int argc, char **argv)
{
  std::cout << "\tTest UDP Client" << std::endl;
  client = new MainClient();
  client->Connect(ip, port);

  return PressAnyKey();
}

int PressAnyKey()
{
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}