#include "declerations.h"

#include <Core/System.h>

SYSTEM(System_Dumby_1) {
  friend class Core::Singleton<System_Dumby_1>;
public:        
  void  Initialise  () override { Core::System::Initialise(); }
  void  Startup     () override { Core::System::Startup();    }
  void  Update      () override { Core::System::Update();     }
  void  Quit        () override { Core::System::Quit();       }
  void  Shutdown    () override { Core::System::Shutdown();   }
protected:
  System_Dumby_1() : Core::System() {}
};

SYSTEM(System_Dumby_2) {
  friend class Core::Singleton<System_Dumby_2>;
public:
  void  Initialise  () override { Core::System::Initialise(); }
  void  Startup     () override { Core::System::Startup();    }
  void  Update      () override { Core::System::Update();     }
  void  Quit        () override { Core::System::Quit();       }
  void  Shutdown    () override { Core::System::Shutdown();   }
protected:
  System_Dumby_2() : Core::System() { Requires<System_Dumby_1>(); }
};

namespace Core_Test {



}