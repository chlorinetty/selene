#include "log.hxx"

#include "Arduino.h"

namespace selene::system::log
{
  void selenelog::info(const char *tag, const char *fmt, ...)
  {
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    Serial.printf("i %10lu (%s): %s\r\n", millis(), tag, buffer);
  }

  void selenelog::warn(const char *tag, const char *fmt, ...)
  {
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    Serial.printf("w %10lu (%s): %s\r\n", millis(), tag, buffer);
  }

  void selenelog::error(const char *tag, const char *fmt, ...)
  {
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    Serial.printf("e %10lu (%s): %s\r\n", millis(), tag, buffer);
  }
}