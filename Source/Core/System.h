#pragma once

#include "Module.h"
#include "Singleton.h"

#include <set>
#include <unordered_map>

namespace Core {

  /// <summary>
  /// Class used for setting up and monitoring the state of the system's modules.
  /// </summary>
  class System :
    public Singleton<System>,
    public Module::Observer {
    friend Module;
    friend Singleton;
  public:
    /// <summary>
    /// Enumerator for identifying the state of a module or system.
    /// </summary>
    enum  State {
      INACTIVE        = 0,
      INITIALISING    = 1,
      STARTING_UP     = 2,
      ACTIVE          = 3,
      QUITTING        = 4,
      SHUTTING_DOWN   = 5,
      FAILED          = 6
    };

    /// <summary>
    /// Iterates through and intialises all the required modules in order to successfully carry out the functionality of the provided module.
    /// </summary>
    /// <param name = "module">The module to be initialised and ran by the system.</param>
    void  Initialise            (Module* const);

    /// <summary>
    /// Configures the system, establishing the startup priority order.
    /// </summary>
    void  Configure             ();

    /// <summary>
    /// Iterates through and starts up all the modules registered within the system.
    /// </summary>
    void  Startup               ();

    /// <summary>
    /// Monitors the
    /// </summary>
    void  Update                ();

    /// <summary>
    /// Iterates through and quits all the modules registered within the system.
    /// </summary>
    void  Quit                  ();

    /// <summary>
    /// Iterates through and shuts down all the modules registered within the system.
    /// </summary>
    void  Shutdown              ();
  protected:
          /// <summary>
          /// Constructor. Registers as global module observer.
          /// </summary>
          System                ();

          /// <summary>
          /// Destructor. Unregisters as global module observer.
          /// </summary>
          ~System               ();

    /// <summary>
    /// Iterates through and quits all dependent modules in order to ensure that the provided module is no longer needed.
    /// </summary>
    /// <param name = "module">The module to quit out.</param>
    void  Quit                  (Module* const);

    /// <summary>
    /// Acknowledges that a module is initialising.
    /// </summary>
    /// <param name = "module">The module that is initialising.</param>
    void  onInitialise          (Module* const) final override;

    /// <summary>
    /// Acknowledges that a module is starting up.
    /// </summary>
    /// <param name = "module">The module that is starting up.</param>
    void  onStartup             (Module* const) final override;

    /// <summary>
    /// Acknowledges that a module is updatting.
    /// </summary>
    /// <param name = "module">The module that is updating.</param>
    void  onUpdate              (Module* const) final override;

    /// <summary>
    /// Acknowledges that a module is quitting.
    /// </summary>
    /// <param name = "module">The module that is quitting.</param>
    void  onQuit                (Module* const) final override;

    /// <summary>
    /// Acknowledges that a module is shutting down.
    /// </summary>
    /// <param name = "module">The module that is shutting down.</param>
    void  onShutdown            (Module* const) final override;

    /// <summary>
    /// Establishes the module with its associated name.
    /// </summary>
    /// <param name = "module">The module being configured.</param>
    /// <param name = "name"></param>
    void  ConfigureModule       (Module* const, const DTU::String&);

    /// <summary>
    /// Establishes the startup priority level of the named module.
    /// Modules startup in order of lowest priority value first.
    /// Priority levels default to 0.
    /// </summary>
    /// <param name = "name">The name of the module having its priority level set.</param>
    /// <param name = "priority">The new priority level of the module.</param>
    void  ConfigurePriortiy     (const DTU::String&, const int8_t);

    /// <summary>
    /// Establishes dependencies between the two provided modules.
    /// </summary>
    /// <param name = "dependent">The depending module.</param>
    /// <param name = "requirement">The required module.</param>
    void  ConfigureRequirement  (Module* const, Module* const);

  private:
    /// <summary>
    /// A container class to hold information required to manage modules.
    /// </summary>
    struct ModuleConfig {
      DTU::String         name          { "" };
      std::set<Module*>   requirements  {};
      std::set<Module*>   dependents    {};
      System::State       state         { State::INACTIVE };
      int8_t              priority      { 0 };
    };
    typedef std::unordered_map<Module*, ModuleConfig> ModuleConfiguration;
    
    System::State         m_globalState   { State::INACTIVE };
    ModuleConfiguration   m_moduleConfig  {};
  };

#define SYSTEM Core::System::Instance()

}