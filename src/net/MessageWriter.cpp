#include "MessageWriter.hpp"

MessageWriter::MessageWriter() { oss = std::ostringstream(std::ios::binary); }

// 1 byte
void MessageWriter::Write(bool value) {
  oss.write(reinterpret_cast<const char *>(&value),
            sizeof(value));
}

// 1 byte
void MessageWriter::Write(char value) {
  //oss.write(&value, sizeof(value));
  oss.write(reinterpret_cast<const char *>(&value),
            sizeof(value));
}

// 2 byte
void MessageWriter::Write(short value) {
  oss.write(reinterpret_cast<const char *>(&value),
            sizeof(value));
}

// 2 byte
void MessageWriter::Write(unsigned short value) {
  oss.write(reinterpret_cast<const char *>(&value),
            sizeof(value));
}

// 4 byte
void MessageWriter::Write(int value) {
  oss.write(reinterpret_cast<const char *>(&value),
            sizeof(value));
}

// 4 byte
void MessageWriter::Write(unsigned int value) {
  oss.write(reinterpret_cast<const char *>(&value),
            sizeof(value));
}

// 4 byte
void MessageWriter::Write(float value) {
  oss.write(reinterpret_cast<const char *>(&value),
            sizeof(value));
}

// utf8 char array string
void MessageWriter::Write(const char *value) {
  if (strlen(value) > 255) {
    throw std::exception("MessageWriter error: string size > 255");
  }
  char length = strlen(value); // Получаем длину строки
  //oss << length;
  oss.write(reinterpret_cast<const char *>(&length),
            sizeof(length)); // Запись длины строки
  oss.write(value, length);  // Запись самой строки
}

// utf8 string
void MessageWriter::Write(std::string value) {
  /*if (value.size() > 255) {
    throw std::exception("MessageWriter error: string size > 255");
  }
  char length = value.size(); // Получаем длину строки
  oss.write(reinterpret_cast<const char *>(&length),
            sizeof(length));       // Запись длины строки
  oss.write(value.data(), length); // Запись самой строки*/
  Write(value.c_str());
}

std::string MessageWriter::GetData() { return oss.str(); }