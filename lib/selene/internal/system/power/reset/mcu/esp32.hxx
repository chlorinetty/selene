#pragma once

#if defined(ARDUINO_ARCH_ESP32)

extern "C"
{
#include "esp_system.h"
}

namespace selene::system::power::_impl_reset
{
  inline void reset() { esp_restart(); }
}

#endif