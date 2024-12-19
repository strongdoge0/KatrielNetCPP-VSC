#pragma once
// Alt+Shift+F

#include <iostream>
#include <string>
#include <sstream>
//#include <codecvt>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
//#include <windows.h>
#include "../net/NetHelper.hpp"
#include "../net/MainClient.hpp"
#include "../net/WebRequest.hpp"
#include "../net/MessageWriter.hpp"
#include "../net/MessageReader.hpp"

int g_argc;
char **g_argv;

