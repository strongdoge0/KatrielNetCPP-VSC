// Класс для бинарной записи данных в поток
/* Список поддерживаемых типов:
    bool
    char
    short
    unsigned short
    int
    unsigned int
    float
    const char*
    std::string
*/
// Максимальный размер строк 255

#pragma once

#include <iostream>
#include <string>
#include <sstream>

class MessageWriter{
    public:
    MessageWriter();
    
    void Write(bool value); // 1 byte
    void Write(char value); // 1 byte
    void Write(short value); // 2 byte
    void Write(unsigned short value); // 2 byte
    void Write(int value); // 4 byte
    void Write(unsigned int value); // 4 byte
    void Write(float value); // 4 byte
    void Write(const char* value); // utf8 char array string
    void Write(std::string value); // utf8 string
    
    std::string GetData();
    
    private:
    std::ostringstream oss;
};