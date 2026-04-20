#pragma once

#if defined(ARDUINO_ARCH_AVR)
#warning "selene::system::power->reset() -> TODO-stage, unsupported mcu!"
#elif defined(ARDUINO_ARCH_ESP32)
#include "mcu/esp32.hxx"
#elif defined(ARDUINO_ARCH_STM32)
#warning "selene::system::power->reset() -> TODO-stage, unsupported mcu!"
#else
#error "selene::system::power->reset() -> unsupported mcu!"
#endif