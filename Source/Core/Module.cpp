#include "Module.h"

namespace Core {

  Module::Module(const std::string& name) {

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