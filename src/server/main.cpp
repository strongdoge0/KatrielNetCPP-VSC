#include "main.hpp"

int PressAnyKey();


int main(int argc, char **argv)
{
  std::cout << "\tTest UDP Server" << std::endl;

  return PressAnyKey();
}

int PressAnyKey()
{
  char anyKey;
  std::cin >> anyKey;
  return EXIT_SUCCESS;
}