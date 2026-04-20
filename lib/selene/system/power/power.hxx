#pragma once

#include "reset/impl.hxx"

namespace selene::system::power
{
  inline void reset_mcu() { _impl_reset::reset(); }
}