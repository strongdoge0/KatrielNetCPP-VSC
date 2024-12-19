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
  bool result;
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
  char /*size_t*/ readLength = 0;
  iss.read(reinterpret_cast<char *>(&readLength), sizeof(readLength));
  if (readLength > 0) {
    //char readText[255];
    char readText[readLength];
    iss.read(readText, readLength); // Чтение самой строки
    readText[readLength] = '\0'; // Завершаем строку нулевым символом
    return readText;
    //const char *result;
    //strcpy((char*)result, readText);
    //return result;
  } else {
    return "";
  }
}

// utf8 string
std::string MessageReader::ReadString() {
  // return std::string(ReadCString());
  char /*size_t*/ readLength = 0;
  iss.read(reinterpret_cast<char *>(&readLength), sizeof(readLength)); //
  if (readLength > 0) {
    char readCStr[readLength];
    iss.read(readCStr, readLength);

    return std::string(readCStr);
  } else {
    return "";
  }
}