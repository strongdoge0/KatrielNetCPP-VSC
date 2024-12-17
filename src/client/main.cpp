#include "main.hpp"


int PressAnyKey();

void ClientApp(){
  std::cout << "\tTest UDP Client" << std::endl;
}

int main(int argc, char **argv)
{
  ClientApp();

  return PressAnyKey();
}

int PressAnyKey()
{
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}