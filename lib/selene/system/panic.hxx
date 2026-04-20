#pragma once

namespace selene::system
{
  /// @brief Send panic!
  /// @param msg Message sent to the serial adapter.
  void panic(const char *msg);
}