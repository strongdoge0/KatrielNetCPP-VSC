//Header

#pragma once

#include "../net/NetHelper.hpp"
#include "../net/WebRequest.hpp"
#include "../net/MessageWriter.hpp"
#include "../net/MessageReader.hpp"
#include "../net/MessageFlag.hpp"
#include "../net/MessageType.hpp"
#include "../net/LogType.hpp"
#include "../net/ConnectionState.hpp"

#if defined(_SERVER)
    #include "MainServer.hpp"
#elif defined(_CLIENT)
    #include "MainClient.hpp"
#endif