#include "Module.h"

#include "System.h"

namespace Core {

  Module::Module(const DTU::String& name) {
    SYSTEM->ConfigureModule(this, name);
  }

  void Module::Requires(Module* const req) {
    SYSTEM->ConfigureRequirement(this, req);
  }

}