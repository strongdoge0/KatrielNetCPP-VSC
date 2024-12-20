#include "MainServer.hpp"

bool MainServer::IsListening(){
    return _listening;
}

bool MainServer::IsActive(){
    return true;
}

void MainServer::Log(std::string message, LogType logType){
    
}

bool MainServer::Listen(int port){
    _port = port;
    _listening = true;

    
    listenCallbackThread = new std::thread(std::bind(&MainServer::ListenCallback, this));
    
    return true;
}

void MainServer::ListenCallback(){
    std::cout << "UDP server start listening at " << NetHelper::SockaddrToString(_server_addr) << std::endl;
    while(_listening){
        
    }
}

void MainServer::PollEvents(){
    
}

void MainServer::Disconnect(ConnectionState connectionState){
    
}

void MainServer::Close(){
    
}

void MainServer::Stop(){
    
}


