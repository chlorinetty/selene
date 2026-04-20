#pragma once

#if defined(ARDUINO_ARCH_AVR)

extern "C"
{
#include "avr/wdt.h"
}

namespace selene::system::power::_impl_reset
{
  inline void reset()
  {
    wdt_enable(WDTO_15MS);
    while (true)
    {
    }
  }
}

#endif