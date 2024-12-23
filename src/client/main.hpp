#pragma once
// Alt+Shift+F

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <any>
//#include <codecvt>

#ifdef _WIN32 // для Windows
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#elif __linux__ // для Linux
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
// неизвестная ОС
#endif

#define _CLIENT
#include "../net/KatrielNet.hpp"

int g_argc;
char **g_argv;

