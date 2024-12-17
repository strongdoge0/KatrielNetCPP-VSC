#include "main.hpp"

int PressAnyKey();

void ServerApp(){
  std::cout << "\tTest UDP Server" << std::endl;
}


int main(int argc, char **argv)
{
  ServerApp();

  return PressAnyKey();
}

int PressAnyKey()
{
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}