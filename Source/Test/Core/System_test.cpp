#include "declerations.h"

#include <Core/System.h>

enum  ModuleState { INIT = 0, START = 1, UPDATE = 2, QUIT = 3, STOP = 4 };
int   counter[5]  { 0,0,0,0,0 };

class Module_Ticker {
public:
  int   getCounter(ModuleState idx)  { return m_counter[idx]; }
protected:
  void  Tick(ModuleState idx) { m_counter[idx] = counter[idx]++; }
private:
  int   m_counter[5]  { 0,0,0,0,0 };
};

MODULE(Module_Dumby_1), public Module_Ticker {
  MODULE_REQUIRES(Module_Dumby_1, void)
public:
  void  Initialise  () override { Core::Module::Initialise(); Tick(INIT);   }
  void  Startup     () override { Core::Module::Startup();    Tick(START);  }
  void  Update      () override { Core::Module::Update();     Tick(UPDATE); }
  void  Quit        () override { Core::Module::Quit();       Tick(QUIT);   }
  void  Shutdown    () override { Core::Module::Shutdown();   Tick(STOP);   }
};

MODULE(Module_Dumby_2), public Module_Ticker {
  MODULE_REQUIRES(Module_Dumby_2, Module_Dumby_1)
public:
  void  Initialise  () override { Core::Module::Initialise(); Tick(INIT);   }
  void  Startup     () override { Core::Module::Startup();    Tick(START);  }
  void  Update      () override { Core::Module::Update();     Tick(UPDATE); }
  void  Quit        () override { Core::Module::Quit();       Tick(QUIT);   }
  void  Shutdown    () override { Core::Module::Shutdown();   Tick(STOP);   }
protected:
};

MODULE(Module_Dumby_3), public Module_Ticker {
  MODULE_REQUIRES(Module_Dumby_3, Module_Dumby_1, Module_Dumby_2)
public:
  void  Initialise  () override { Core::Module::Initialise(); Tick(INIT);   }
  void  Startup     () override { Core::Module::Startup();    Tick(START);  }
  void  Update      () override { Core::Module::Update();     Tick(UPDATE); }
  void  Quit        () override { Core::Module::Quit();       Tick(QUIT);   }
  void  Shutdown    () override { Core::Module::Shutdown();   Tick(STOP);   }
protected:
};

void Core::System::Configure() {
  ConfigurePriortiy("Module_Dumby_2", -1);
  ConfigurePriortiy("Module_Dumby_3", 2);
  ConfigurePriortiy("Module_Dumby_1", 3);
}

namespace Core_Test {

  void System::Reset() {
    SYSTEM->Shutdown();
    SYSTEM->Configure();

    counter[0] = 0;
    counter[1] = 0;
    counter[2] = 0;
    counter[3] = 0;
    counter[4] = 0;
  }

  void System::Examine() {
    TestCase([]() {
      SYSTEM->Initialise(Module_Dumby_3::Instance());

      return Module_Dumby_3::Instance()->getCounter(INIT) == 2
        && Module_Dumby_2::Instance()->getCounter(INIT) == 1
        && Module_Dumby_1::Instance()->getCounter(INIT) == 0;
    }, "System::Initialise");

    TestCase([]() {
      SYSTEM->Initialise(Module_Dumby_3::Instance());
      SYSTEM->Startup();

      return Module_Dumby_1::Instance()->getCounter(START) == 2
        && Module_Dumby_3::Instance()->getCounter(START) == 1
        && Module_Dumby_2::Instance()->getCounter(START) == 0;
    }, "System::Startup");

    TestCase([]() {
      SYSTEM->Initialise(Module_Dumby_3::Instance());
      SYSTEM->Startup();
      SYSTEM->Quit();

      return Module_Dumby_1::Instance()->getCounter(QUIT) == 2
        && Module_Dumby_2::Instance()->getCounter(QUIT) == 1
        && Module_Dumby_3::Instance()->getCounter(QUIT) == 0;
    }, "System::Quit");
  }

}