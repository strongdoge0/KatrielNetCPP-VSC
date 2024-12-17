#pragma once
// Alt+Shift+F

#include <iostream>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
//#include <windows.h>
#include "../net/NetHelper.hpp"
#include "../net/MainServer.hpp"
#include "../net/WebRequest.hpp"

int g_argc;
char **g_argv;