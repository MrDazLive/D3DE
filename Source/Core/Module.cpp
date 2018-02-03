#include "Module.h"

#include "System.h"

namespace Core {

  Module::Module(const DTU::String& name) {
    SYSTEM->ConfigureModule(this, name);
  }

  void Module::Requires(Module* const req) {
    SYSTEM->ConfigureRequirement(this, req);
  }

  void Module::Initialise() {
    NotifyObservers(&Observer::onInitialise, this);
  }
  
  void Module::Startup() {
    NotifyObservers(&Observer::onStartup, this);
  }
    
  void Module::Update() {
    NotifyObservers(&Observer::onUpdate, this);
  }

  void Module::Quit() {
    NotifyObservers(&Observer::onQuit, this);
  }
  
  void Module::Shutdown() {
    NotifyObservers(&Observer::onShutdown, this);
  }

}