#pragma once

#include "Module.h"
#include "Singleton.h"

#include <set>
#include <unordered_map>

namespace Core {

  class System :
    public Singleton<System>,
    public Module::Observer {
    friend Module;
    friend Singleton;
  public:

    enum State {
      INACTIVE        = 0,
      INITIALISING    = 1,
      STARTING_UP     = 2,
      ACTIVE          = 3,
      QUITTING        = 4,
      SHUTTING_DOWN   = 5,
      FAILED          = 6
    };

    void  Configure             ();
    void  Initialise            (Module* const);
    void  Startup               ();
    void  Update                ();
    void  Quit                  ();
    void  Shutdown              ();
  protected:
          System                ();
          ~System               ();

    void  Quit                  (Module* const);

    void  onInitialise          (Module* const) final override;
    void  onStartup             (Module* const) final override;
    void  onUpdate              (Module* const) final override;
    void  onQuit                (Module* const) final override;
    void  onShutdown            (Module* const) final override;

    void  ConfigureModule       (Module* const, const std::string&);
    void  ConfigurePriortiy     (const std::string&, const int8_t);
    void  ConfigureRequirement  (Module* const, Module* const);

  private:
    struct ModuleConfig {
      std::string         name          { "" };
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