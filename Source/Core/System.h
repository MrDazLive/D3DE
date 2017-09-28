#pragma once

#include "Singleton.h"

#include <set>

namespace Core {

  class System {
  public:
    virtual void        Initialise      ();
    virtual void        Startup         ();
    virtual void        Update          ();
    virtual void        Quit            ();
    virtual void        Shutdown        ();
  protected:
                        System          () = default;
    virtual             ~System         () = default;

    template <typename T>
    void                Requires        ();
  private:
    void                Requires        (System* const);

    std::set<System*>   m_requirements  {};
    std::set<System*>   m_dependents    {};
  };

  #define SYSTEM(T) class T : public Core::System, public Core::Singleton<T>

  void System::Requires(System* const ptr) {
    m_requirements.emplace(ptr);
    ptr->m_dependents.emplace(this);
  }

  template <typename T>
  void System::Requires() {
    Requires(T::Instance());
  }

}