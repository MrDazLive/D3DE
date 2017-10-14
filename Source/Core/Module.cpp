#include "Module.h"

#include "System.h"

namespace Core {

  template <>
  std::set<Observable<Module>::Observer*> Observable<Module>::s_globalObservers = {};

  Module::Module(const DTU::String& name) {
    SYSTEM->ConfigureModule(this, name);
  }

  void Module::Requires(Module* const req) {
    SYSTEM->ConfigureRequirement(this, req);
  }

  void Module::Initialise() {
    NOTIFY_OBSERVERS(onInitialise(this));
  }
  
  void Module::Startup() {
    NOTIFY_OBSERVERS(onStartup(this));
  }
    
  void Module::Update() {
    NOTIFY_OBSERVERS(onUpdate(this));
  }

  void Module::Quit() {
    NOTIFY_OBSERVERS(onQuit(this));
  }
  
  void Module::Shutdown() {
    NOTIFY_OBSERVERS(onShutdown(this));
  }

}