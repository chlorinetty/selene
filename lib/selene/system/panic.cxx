#include "panic.hxx"

#include "log/log.hxx"
#include "power/power.hxx"

namespace selene::system
{
  void panic(const char *msg)
  {
    log::selenelog::error("selene/panic", "%s", msg);
    power::reset_mcu();
  }
}