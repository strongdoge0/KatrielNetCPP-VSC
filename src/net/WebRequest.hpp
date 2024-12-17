#pragma once

#include <iostream>
#include <string>

//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib/httplib.h>

class WebRequest{
    public:
    static std::string Get(std::string website, std::string path, std::string username, std::string password);
    static std::string Get(std::string website, std::string path, std::string cookie);
};