#pragma once
// Alt+Shift+F

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <any>
//#include <codecvt>

//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
//#include <windows.h>

#define _CLIENT
#include "../net/KatrielNet.hpp"

int g_argc;
char **g_argv;

