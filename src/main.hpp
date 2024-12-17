#pragma once
// Alt+Shift+F

#include <iostream>
#include <string>

#define _ServerBuild

#ifdef _ServerBuild
#include "net/MainServer.hpp"
#else
#include "net/MainClient.hpp"
#endif
