#pragma once

#include <iostream>
#include <string>
#include <thread>

#include "KatrielNet.hpp"

class MainServer {
public:
    bool noDelay = true;
    
    void (*OnLogCallback)(std::string logString, LogType logType) = nullptr;
    void (*OnStartCallback)() = nullptr;
    void (*OnStopCallback)() = nullptr;
    void (*OnCloseCallback)() = nullptr;
    //void (*OnAcceptCallback)(IPEndPoint endPoint, std::string key) = nullptr;
    void (*OnConnectCallback)(ConnectionState connectionState) = nullptr;
    void (*OnDisconnectCallback)(ConnectionState connectionState) = nullptr;
    void (*OnReceiveCallback)(ConnectionState connectionState, std::string data) = nullptr;
    
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
    std::thread *listenCallbackThread;
    SOCKET *_sockfd = nullptr;
    const sockaddr *_server_addr = nullptr;
    
    void Log(std::string message, LogType logType = LogType::Default);
    //byte[] GetBytes(params object[] args)
    //bool UpdateConnectionState(ConnectionState connectionState);
    void Close();
    
};