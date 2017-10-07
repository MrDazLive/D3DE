#pragma once

#include "Singleton.h"
#include "Observer.h"

namespace Core {

  /// <summary>
  /// Base class to be used when establishing a new system module.
  /// </summary>
  /// <b>Example</b><br/>
  /// <code>
  /// MODULE(My_Module) {
  ///   MODULE_REQUIRES(My_Module, Needed_Module)
  /// public:
  ///   /* override virtuals */
  /// };
  /// </code>
  class Module : public Observable<Module> {
  public:
    virtual void        Initialise      ();
    virtual void        Startup         ();
    virtual void        Update          ();
    virtual void        Quit            ();
    virtual void        Shutdown        ();
  protected:
                        Module          (const std::string&);
    virtual             ~Module         () = default;

    template <typename T>
    inline void                Requires        ();
    template <typename T1, typename T2, typename ... V>
    inline void                Requires        ();
  private:
    void                Require         (Module* const);
  };

  OBSERVER_CLASS(Module) {
  public:
    virtual void  onInitialise  (Module* const) {}
    virtual void  onStartup     (Module* const) {}
    virtual void  onUpdate      (Module* const) {}
    virtual void  onQuit        (Module* const) {}
    virtual void  onShutdown    (Module* const) {}
  };

  #define MODULE(T)                                           \
  class T : public Core::Module, public Core::Singleton<T>    \

  #define MODULE_REQUIRES(T, ...)                             \
  friend class Core::Singleton<T>;                            \
  protected:                                                  \
    T() : Core::Module("T") { Requires<__VA_ARGS__>(); }      \

  template <typename T>
  inline void Module::Requires() {
    Require(T::Instance());
  }

  template <>
  inline void Module::Requires<void>() {}

  template <typename T1, typename T2, typename ... V>
  inline void Module::Requires () {
    Requires<T1>();
    Requires<T2, V...>();
  }

}