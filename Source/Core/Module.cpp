#include "Module.h"

#include "System.h"

namespace Core {

  template <>
  std::set<Observable<Module>::Observer*> Observable<Module>::s_globalObservers = {};

  Module::Module(const std::string& name) {
    SYSTEM->ConfigureModule(this, name);
  }

  void Module::Require(Module* const req) {
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