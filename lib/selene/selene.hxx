#pragma once

namespace selene
{
  enum class ModuleState
  {
    REGISTERED,
    STARTED,
    STOPPED
  };

  enum class SELERR {
    //* General
    OK = 0,
    BAD = 1,

    //* System
    ESINVVALUE, //? invalid value
    ESNOTIMPLD, //? not implemented

    //* Init
    EIMNOSPACE, //? no space for new module
    EIMNOFOUND, //? module not found
    EIMODINULL, //? module is null
    EIMODDUPLI, //? module with the same name already exists
    EIMODISTOP, //? module is stopped
    EIMODFTASK, //? module failed to task
    EIMODILSTA, //? module requested in an illegal state

    //* Networking
    ENNETIDOWN, //? network down
    ENNOTREACH, //? network unreachable
    ENTIMEDOUT, //? connection timed out
    ENCONREFSD, //? connection refused
    ENHOSTDOWN, //? host is down


  };

  class selene
  {
  private:
  public:
    selene();

  private:
  };
}