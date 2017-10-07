#pragma once

#include "Singleton.h"
#include "Observer.h"

namespace Core {

  /// <summary>
  /// Base class to be used when establishing a new system module.
  /// </summary>
  /// <b>Examples</b><br/>
  /// <i>Establishing modules with no requirements.</i>
  /// <code>
  /// MODULE(My_Module) {
  ///   MODULE_REQUIRES(My_Module, void)
  /// public:
  ///   /* override virtuals */
  /// };
  /// </code>
  /// <i>Establishing modules with requirements.</i>
  /// <code>
  /// MODULE(My_Module) {
  ///   MODULE_REQUIRES(My_Module, Needed_Module)
  /// public:
  ///   /* override virtuals */
  /// };
  /// </code>
  class Module : public Observable<Module> {
  public:
    /// <summary>
    /// The base initialise function for each module.
    /// Used to establish core functionality required by dependent systems.
    /// To be called up following construction.
    /// </summary>
    virtual void        Initialise      ();

    /// <summary>
    /// The base startup function for each module.
    /// Used to prepare non-core aspects of the module prior to the core loop.
    /// To be called prior to update.
    /// </summary>
    virtual void        Startup         ();

    /// <summary>
    /// The base update function for each module.
    /// Used to perform the ongoing functionality of the module.
    /// To be continuously called throughout the lifespan of the applicaiton.
    /// </summary>
    virtual void        Update          ();

    /// <summary>
    /// The base quit function for each module.
    /// Used to cleanup non-fundamental aspects of the module.
    /// To be called following the termination of update.
    /// </summary>
    virtual void        Quit            ();

    /// <summary>
    /// The base shutdown module for each module.
    /// Used to ensure that the module is safely cleaned up prior to termination of the process.
    /// To be called prior to terminating the application process.
    /// </summary>
    virtual void        Shutdown        ();
  protected:
                        /// <summary>
                        /// Constructor.
                        /// </summary>
                        /// <param name = "name">The name of the class.</param>
                        Module          (const std::string&);
                        
                        /// <summary>
                        /// Default virtual constructor.
                        /// </summary>
    virtual             ~Module         () = default;

    /// <summary>
    /// Tells the module to register the provided module as a requirement.
    /// </summary>
    template <typename T>
    inline void         Requires        ();

    /// <summary>
    /// Tells the module to register the provided modules as requirements.
    /// </summary>
    template <typename T1, typename T2, typename ... V>
    inline void         Requires        ();
  private:
    /// <summary>
    /// Associates the required modules.
    /// </summary>
    /// <param name = "req">The pointer to the required module.</param>
    void                Requires         (Module* const);
  };
  
  /// <summary>
  /// Base class used to notify observers of the module state.
  /// </summary>
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
    T() : Core::Module(#T) { Requires<__VA_ARGS__>(); }       \

  template <typename T>
  inline void Module::Requires() {
    Requires(T::Instance());
  }

  template <>
  inline void Module::Requires<void>() {}

  template <typename T1, typename T2, typename ... V>
  inline void Module::Requires() {
    Requires<T1>();
    Requires<T2, V...>();
  }

}