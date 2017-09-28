#include "System.h"

namespace Core {

  void System::Initialise() {
    for(System* const ptr : m_requirements) {
      ptr->Initialise();
    }
  }
  
  void System::Startup() {
  
  }
    
  void System::Update() {
    
  }

  void System::Quit() {
    for(System* const ptr : m_dependents) {
      ptr->Quit();
    }
  }
  
  void System::Shutdown() {

  }

}