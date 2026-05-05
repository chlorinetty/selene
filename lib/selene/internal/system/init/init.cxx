#include "init.hxx"

#include "Arduino.h"

namespace selene::system::init
{
  SELERR
  seleneinit::register_module(const char *name, selenemodule *smodule)
  {
    if (this->count >= MODULES_SIZE)
      return SELERR::EIMNOSPACE;

    if (find(name) != -1)
      return SELERR::EIMODDUPLI;

    this->modules[count++] = {.name = name,
                              .smodule = smodule,
                              .state = ModuleState::REGISTERED};

    return SELERR::OK;
  }

  SELERR
  seleneinit::state(const char *name, ModuleState &out) const
  {
    int pos = find(name);
    if (pos == -1)
      return SELERR::EIMNOFOUND;

    return this->state(pos, out);
  }

  SELERR
  seleneinit::state(size_t index, ModuleState &out) const
  {
    if (index >= this->count)
      return SELERR::ESINVVALUE;

    out = this->modules[index].state;
    return SELERR::OK;
  }

  SELERR
  seleneinit::start(const char *name)
  {
    int pos = find(name);
    if (pos == -1)
      return SELERR::EIMNOFOUND;

    return start(pos);
  }

  SELERR
  seleneinit::start(size_t index)
  {
    if (index >= this->count)
      return SELERR::ESINVVALUE;

    auto &mod = this->modules[index];
    if (!mod.smodule)
      return SELERR::EIMODINULL;

    if (mod.state != ModuleState::REGISTERED &&
        mod.state != ModuleState::STOPPED)
      return SELERR::EIMODILSTA;

    mod.state = (mod.smodule->start() == 0) ? ModuleState::STARTED : ModuleState::STOPPED;

    if (mod.state != ModuleState::STARTED)
      return SELERR::EIMODISTOP;

    return SELERR::OK;
  }

  SELERR
  seleneinit::start_all(void)
  {
    bool all_ok = true;
    for (size_t i = 0; i < this->count; i++)
      if (start(i) != SELERR::OK)
        all_ok = false;
    return all_ok ? SELERR::OK : SELERR::EIMODISTOP;
  }

  SELERR
  seleneinit::task(const char *name)
  {
    int pos = find(name);
    if (pos == -1)
      return SELERR::EIMNOFOUND;

    return task(pos);
  }

  SELERR
  seleneinit::task(size_t index)
  {
    if (index >= this->count)
      return SELERR::ESINVVALUE;

    auto &mod = this->modules[index];
    if (!mod.smodule)
      return SELERR::EIMODINULL;

    if (mod.state != ModuleState::STARTED)
      return SELERR::EIMODILSTA;

    return (mod.smodule->task() == 0) ? SELERR::OK : SELERR::EIMODFTASK;
  }

  SELERR
  seleneinit::task_all(void)
  {
    bool all_ok = true;
    for (size_t i = 0; i < this->count; i++)
      if (task(i) != SELERR::OK)
        all_ok = false;
    return all_ok ? SELERR::OK : SELERR::EIMODFTASK;
  }

  SELERR
  seleneinit::stop(const char *name)
  {
    int pos = find(name);
    if (pos == -1)
      return SELERR::EIMNOFOUND;

    return stop(pos);
  }

  SELERR
  seleneinit::stop(size_t index)
  {
    if (index >= this->count)
      return SELERR::ESINVVALUE;

    auto &mod = this->modules[index];
    if (!mod.smodule)
      return SELERR::EIMODINULL;

    if (mod.state != ModuleState::STARTED)
      return SELERR::EIMODILSTA;

    mod.state = ModuleState::STOPPED;
    return SELERR::OK;
  }

  SELERR
  seleneinit::stop_all(void)
  {
    bool all_ok = true;
    for (size_t i = count; i-- > 0;)
      if (stop(i) != SELERR::OK)
        all_ok = false;
    return all_ok ? SELERR::OK : SELERR::EIMODILSTA;
  }

  int seleneinit::find(const char *name) const
  {
    for (size_t i = 0; i < count; i++)
      if (strcmp(this->modules[i].name, name) == 0)
        return i;
    return -1;
  }
}