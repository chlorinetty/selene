#include "init.hxx"

#include <string.h>

using namespace selene::types::system::init;
namespace selene::system::init
{
  InitResponse
  seleneinit::register_module(const char *name, selenemodule *smodule)
  {
    if (this->count >= MODULES_SIZE)
      return InitResponse::ENOSPACE;

    if (find(name) != -1)
      return InitResponse::EMODDUPL;

    this->modules[count++] = {.name = name,
                              .smodule = smodule,
                              .state = ModuleState::REGISTERED};

    return InitResponse::OK;
  }

  InitResponse
  seleneinit::state(const char *name, ModuleState &out) const
  {
    int pos = find(name);
    if (pos == -1)
      return InitResponse::ENOFOUND;

    return this->state(pos, out);
  }

  InitResponse
  seleneinit::state(size_t index, ModuleState &out) const
  {
    if (index >= this->count)
      return InitResponse::EISOUTOB;

    out = this->modules[index].state;
    return InitResponse::OK;
  }

  InitResponse
  seleneinit::start(const char *name)
  {
    int pos = find(name);
    if (pos == -1)
      return InitResponse::ENOFOUND;

    return start(pos);
  }

  InitResponse
  seleneinit::start(size_t index)
  {
    if (index >= this->count)
      return InitResponse::EISOUTOB;

    auto &mod = this->modules[index];
    if (!mod.smodule)
      return InitResponse::EMODNULL;

    if (mod.state != ModuleState::REGISTERED &&
        mod.state != ModuleState::STOPPED)
      return InitResponse::EILSTATE;

    mod.state = (mod.smodule->start() == 0) ? ModuleState::STARTED : ModuleState::FAILURE;

    if (mod.state != ModuleState::STARTED)
      return InitResponse::EMODFAIL;

    return InitResponse::OK;
  }

  InitResponse
  seleneinit::start_all(void)
  {
    bool all_ok = true;
    for (size_t i = 0; i < this->count; i++)
      if (start(i) != InitResponse::OK)
        all_ok = false;
    return all_ok ? InitResponse::OK : InitResponse::EMODFAIL;
  }

  InitResponse
  seleneinit::task(const char *name)
  {
    int pos = find(name);
    if (pos == -1)
      return InitResponse::ENOFOUND;

    return task(pos);
  }

  InitResponse
  seleneinit::task(size_t index)
  {
    if (index >= this->count)
      return InitResponse::EISOUTOB;

    auto &mod = this->modules[index];
    if (!mod.smodule)
      return InitResponse::EMODNULL;

    if (mod.state != ModuleState::STARTED)
      return InitResponse::EILSTATE;

    return (mod.smodule->task() == 0) ? InitResponse::OK : InitResponse::EMODFAIL;
  }

  InitResponse
  seleneinit::task_all(void)
  {
    bool all_ok = true;
    for (size_t i = 0; i < this->count; i++)
      if (task(i) != InitResponse::OK)
        all_ok = false;
    return all_ok ? InitResponse::OK : InitResponse::EMODFAIL;
  }

  InitResponse
  seleneinit::stop(const char *name)
  {
    int pos = find(name);
    if (pos == -1)
      return InitResponse::ENOFOUND;

    return stop(pos);
  }

  InitResponse
  seleneinit::stop(size_t index)
  {
    if (index >= this->count)
      return InitResponse::EISOUTOB;

    auto &mod = this->modules[index];
    if (!mod.smodule)
      return InitResponse::EMODNULL;

    if (mod.state != ModuleState::STARTED)
      return InitResponse::EILSTATE;

    mod.state = (mod.smodule->stop() == 0) ? ModuleState::STOPPED : ModuleState::FAILURE;

    if (mod.state != ModuleState::STOPPED)
      return InitResponse::EMODFAIL;

    return InitResponse::OK;
  }

  InitResponse
  seleneinit::stop_all(void)
  {
    bool all_ok = true;
    for (size_t i = count; i-- > 0;)
      if (stop(i) != InitResponse::OK)
        all_ok = false;
    return all_ok ? InitResponse::OK : InitResponse::EMODFAIL;
  }

  int seleneinit::find(const char *name) const
  {
    for (size_t i = 0; i < count; i++)
      if (strcmp(this->modules[i].name, name) == 0)
        return i;
    return -1;
  }
}