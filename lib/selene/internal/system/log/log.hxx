#pragma once

#include <cstddef>

namespace selene::system::log
{
  class selenelog
  {
  private:
    static inline constexpr size_t BUFFER_SIZE = 128;

  public:
    static void info(const char *tag, const char *fmt, ...);
    static void warn(const char *tag, const char *fmt, ...);
    static void error(const char *tag, const char *fmt, ...);

    selenelog() = delete;
  };
}