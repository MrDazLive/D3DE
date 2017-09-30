#include "declerations.h"

#include <Core/Module.h>

MODULE(Module_Dumby_1) {
  MODULE_REQUIRES(Module_Dumby_1)
public:        
  void  Initialise  () override { Core::Module::Initialise(); }
  void  Startup     () override { Core::Module::Startup();    }
  void  Update      () override { Core::Module::Update();     }
  void  Quit        () override { Core::Module::Quit();       }
  void  Shutdown    () override { Core::Module::Shutdown();   }
};

MODULE(Module_Dumby_2) {
  MODULE_REQUIRES(Module_Dumby_2, Module_Dumby_1)
public:
  void  Initialise  () override { Core::Module::Initialise(); }
  void  Startup     () override { Core::Module::Startup();    }
  void  Update      () override { Core::Module::Update();     }
  void  Quit        () override { Core::Module::Quit();       }
  void  Shutdown    () override { Core::Module::Shutdown();   }
protected:
};

MODULE(Module_Dumby_3) {
  MODULE_REQUIRES(Module_Dumby_3, Module_Dumby_1, Module_Dumby_2)
public:
  void  Initialise  () override { Core::Module::Initialise(); }
  void  Startup     () override { Core::Module::Startup();    }
  void  Update      () override { Core::Module::Update();     }
  void  Quit        () override { Core::Module::Quit();       }
  void  Shutdown    () override { Core::Module::Shutdown();   }
protected:
};

namespace Core_Test {



}