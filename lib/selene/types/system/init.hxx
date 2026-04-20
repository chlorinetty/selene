#pragma once

namespace selene::types::system::init
{
  enum class InitResponse
  {
    OK,
    ENOSPACE,
    ENOFOUND,
    EISOUTOB,
    EMODNULL,
    EMODDUPL,
    EMODFAIL,
    EILSTATE
  };

  enum class ModuleState
  {
    REGISTERED,
    CONFIGURED,
    STARTED,
    STOPPED,
    FAILURE
  };
}