#pragma once

#include <cstddef>

#include "types/system/init.hxx"

namespace selene::system::init
{
  class selenemodule
  {
  public:
    virtual ~selenemodule() = default;

    virtual int start() = 0;
    virtual int task() = 0;
    virtual int stop() = 0;
  };

  class seleneinit
  {
  public:
    /// @brief Get count of named modules.
    /// @return Count of named modules.
    int module_count(void) { return count; };

    /// @brief Register a module with a name.
    /// @param name Name of the module.
    /// @param smodule Instance of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    register_module(const char *name, selenemodule *smodule);

    /// @brief Get state of named module.
    /// @param name Name of the module.
    /// @param out State of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    state(const char *name, ModuleState &out) const;
    /// @brief Get state of named module.
    /// @param index Index of the module.
    /// @param out State of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    state(size_t index, ModuleState &out) const;

    /// @brief Start a named module.
    /// @param name Name of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    start(const char *name);
    /// @brief Start a named module.
    /// @param index Index of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    start(size_t index);
    /// @brief Start all named modules.
    /// @return InitResponse - OK if good.
    InitResponse
    start_all(void); // TODO: return failed modules

    /// @brief Run task of a named module.
    /// @param name Name of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    task(const char *name);
    /// @brief Run task of a named module.
    /// @param index Index of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    task(size_t index);
    /// @brief Run tasks of all named modules.
    /// @return InitResponse - OK if good.
    InitResponse
    task_all(void); // TODO: return failed modules

    /// @brief Stop a named module.
    /// @param name Name of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    stop(const char *name);
    /// @brief Stop a named module.
    /// @param index Index of the module.
    /// @return InitResponse - OK if good.
    InitResponse
    stop(size_t index);
    /// @brief Stop all named modules.
    /// @return InitResponse - OK if good.
    InitResponse
    stop_all(void); // TODO: return failed modules

    /// @brief Get the instance of the named module.
    /// @tparam T Type of the named module.
    /// @param name Name of the module.
    /// @return Instance of the module.
    template <typename T>
    T *get(const char *name)
    {
      int pos = find(name);
      if (pos == -1)
        return nullptr;
      return static_cast<T *>(modules[pos].mod);
    }

    /// @brief Get the instance of the named module.
    /// @tparam T Type of the named module.
    /// @param index Index of the module.
    /// @return Instance of the module.
    template <typename T>
    T *get(size_t index)
    {
      if (index >= count)
        return nullptr;
      return static_cast<T *>(modules[index].mod);
    }

  private:
    struct Module
    {
      const char *name;
      selenemodule *smodule;
      ModuleState state;
    };

    static inline constexpr size_t MODULES_SIZE = 24;
    size_t count = 0;
    Module modules[MODULES_SIZE];

    /// @brief Find index of named module. Otherwise -1.
    /// @return Index of the found module.
    int find(const char *name) const;
  };
}