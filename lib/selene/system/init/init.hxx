#pragma once

namespace selene::sys::init
{
  class selenemodule
  {
    virtual ~module() = default;

    virtual int start() = 0;
    virtual int task() = 0;
    virtual int stop() = 0;
  };

  class seleneinit
  {
  public:
  private:
  };
}