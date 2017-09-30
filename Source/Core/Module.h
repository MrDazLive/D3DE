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
  class Module : Observable<Module> {
  public:
    virtual void        Initialise      ();
    virtual void        Startup         ();
    virtual void        Update          ();
    virtual void        Quit            ();
    virtual void        Shutdown        ();
  protected:
                        Module          (const std::string&);
    virtual             ~Module         () = default;

    template <typename ... V>
    void                Requires();
  private:
    template <typename T, typename ... V>
    void                RequiresSplit();
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

  template <typename ... V>
  void Module::Requires() {
    RequiresSplit<V...>();
  }

  template <> void Module::Requires<>() {}

  template <typename T, typename ... V>
  void Module::RequiresSplit() {
    Module* const ptr = T::Instance();
    // TODO: Notify System of requirements & dependancies.

    Requires<V...>();
  }


}