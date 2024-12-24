#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <any>
#include <functional>
#include <mutex>
#include <ctime>

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

#include "KatrielNet.hpp"

class MainServer {
public:
    bool noDelay = true;
    
    void (*OnLogCallback)(std::string logString, LogType logType) = nullptr;
    void (*OnStartCallback)() = nullptr;
    void (*OnStopCallback)() = nullptr;
    void (*OnCloseCallback)() = nullptr;
    //void (*OnAcceptCallback)(IPEndPoint endPoint, std::string key) = nullptr;
    void (*OnConnectCallback)(ConnectionState *connectionState) = nullptr;
    void (*OnDisconnectCallback)(ConnectionState *connectionState) = nullptr;
    void (*OnReceiveCallback)(ConnectionState *connectionState, std::string *data) = nullptr;
    
    bool IsListening();
    bool IsActive();
    bool Listen(int port);
    void ListenCallback();
    //void ReceiveCallback(UdpReceiveResult result, byte[] bytesData);
    //void AcceptConnection(IPEndPoint endPoint, string key);
    //template <typename... T>
    //void SendSingleMessageTo(ConnectionState *connectionState, char id, MessageFlag flag, T... args);
    void SendSingleMessageTo(ConnectionState *connectionState, char id, MessageFlag flag, std::vector<std::any> msg);
    void SendMessageTo(ConnectionState *connectionState, MessageFlag flag, std::vector<std::any> args);
    void PollEvents();
    void Disconnect(ConnectionState *connectionState);
    void Stop();
    
private:
    int _port;
    bool _listening;
    std::thread listenCallbackThread;
    #ifdef _WIN32
    WSADATA wsaData;
    #endif
    SOCKET _serverSocket;
    struct sockaddr_in _serverAddr;
    ActionDispatcher _eventDispatcher;
    //std::unordered_map<sockaddr*, ConnectionState*> _connectionStates;
    std::vector<ConnectionState*> _connectionStates;
    std::mutex _connectionStatesLock;
    
    void Log(std::string message, LogType logType = LogType::Log);
    bool FindConnectionState(struct sockaddr_in *addr);
    void ReadCallback(struct sockaddr_in *addr, std::string data);
    std::string GetHeader(unsigned short size, char id, MessageFlag flag);
    std::string GetData(std::vector<std::any> vector);
    void SendCallback(ConnectionState *connectionState, std::string messageData);
    //bool UpdateConnectionState(ConnectionState connectionState);
    void Close();
    
};