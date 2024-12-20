// Класс для чтения бинарных данных из потока
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

class MessageReader{
    public:
    MessageReader(std::string binaryData);
    
    bool ReadBoolean(); // 1 byte
    char ReadChar(); // 1 byte
    short ReadInt16(); // 2 byte
    unsigned short ReadUInt16(); // 2 byte
    int ReadInt32(); // 4 byte
    unsigned int ReadUInt32(); // 4 byte
    float ReadSingle(); // 4 byte
    const char* ReadCString(); // utf8 char array string
    std::string ReadString(); // utf8 string
    
    std::string GetData();
    
    private:
    std::istringstream iss;
};