#include "main.hpp"

#define _ServerBuild

void ServerApp(){
  std::cout << "\tTest UDP Server" std::endl;
}

void ClientApp(){
  std::cout << "\tTest UDP Client" std::endl;
}

int main(int argc, char **argv)
{
  #ifdef _ServerBuild
  ServerApp();
  #else
  ClientApp();
  #endif
  return PressAnyKey();
}

int PressAnyKey()
{
  if (!Debug::IsEnabled())
    return EXIT_SUCCESS;
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}