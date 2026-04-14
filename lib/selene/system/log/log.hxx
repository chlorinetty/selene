#pragma once

#include <cstddef>

namespace selene::sys::log
{
  class selenelog
  {
  private:
    static inline constexpr size_t BUFFER_SIZE = 128;

  public:
    void info(const char *tag, const char *fmt, ...);
    void warn(const char *tag, const char *fmt, ...);
    void error(const char *tag, const char *fmt, ...);

    selenelog() = delete;
  };
}