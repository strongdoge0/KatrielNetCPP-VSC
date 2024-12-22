#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <functional>
#include <mutex>
#include <ctime>
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

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
    //void SendSingleMessage(ConnectionState connectionState, MessageFlag flag, byte id, params object[] args);
    //void SendMessage(ConnectionState connectionState, MessageFlag flag, params object[] args);
    void PollEvents();
    void Disconnect(ConnectionState connectionState);
    void Stop();
    
private:
    int _port;
    bool _listening;
    std::thread listenCallbackThread;
    WSADATA wsaData;
    SOCKET _serverSocket;
    struct sockaddr_in _serverAddr;
    ActionDispatcher _eventDispatcher;
    std::unordered_map<struct sockaddr_in*, ConnectionState*> _connectionStates;
    std::mutex _connectionStatesLock;
    
    void Log(std::string message, LogType logType = LogType::Log);
    void ReadCallback(struct sockaddr_in *addr, std::string data);
    //byte[] GetBytes(params object[] args)
    //bool UpdateConnectionState(ConnectionState connectionState);
    void Close();
    
};