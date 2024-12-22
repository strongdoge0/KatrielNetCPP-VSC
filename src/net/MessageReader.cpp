#include "MessageReader.hpp"

MessageReader::MessageReader(std::string binaryData) {
  iss = std::istringstream(binaryData, std::ios::binary);
}
// 1 byte
bool MessageReader::ReadBoolean() {
  bool result;
  iss.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

// 1 byte
char MessageReader::ReadChar() {
  char result;
  iss.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

// 2 byte
short MessageReader::ReadInt16() {
  short result;
  iss.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

// 2 byte
unsigned short MessageReader::ReadUInt16() {
  unsigned short result;
  iss.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

// 4 byte
int MessageReader::ReadInt32() {
  int result;
  iss.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

// 4 byte
unsigned int MessageReader::ReadUInt32() {
  unsigned int result;
  iss.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

// 4 byte
float MessageReader::ReadSingle() {
  float result;
  iss.read(reinterpret_cast<char *>(&result), sizeof(result));
  return result;
}

// utf8 char array string
const char *MessageReader::ReadCString() {
  char readLength = 0;
  iss.read(reinterpret_cast<char *>(&readLength), sizeof(readLength)); // Чтение длины строки
  if (readLength > 0) {
    //char readText[readLength]; // так не работает без strcpy
    //std::cout << "read cStr " << (int)readLength << std::endl;
    char *readText = new char[readLength];
    iss.read(readText, readLength); // Чтение самой строки
    readText[(int)readLength] = '\0'; // Завершаем строку нулевым символом
    return readText;
  } else {
    return "";
  }
}

// utf8 string
std::string MessageReader::ReadString() {
  /*char readLength = 0;
  iss.read(reinterpret_cast<char *>(&readLength), sizeof(readLength));
  if (readLength > 0) {
    std::cout << "read str " << (int)readLength << std::endl;
    char readCStr[readLength];
    iss.read(readCStr, readLength);
    readCStr[readLength] = '\0';
    return std::string(readCStr);
  } else {
    return "";
  }*/
  return std::string(ReadCString());
}

std::string MessageReader::GetData() {
  return iss.str();
}