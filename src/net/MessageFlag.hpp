#pragma once

enum class MessageFlag : char {
  None = 0,
  Unreliable = 1,
  Reliable = 2, // гарантия доставки
  Secure = 3, // гарантия доставки с шифрованием AES
  Fail = 4,
  Accept = 5,   // установка соединения
  Success = 6, // успешно доставлен пакет с id
};