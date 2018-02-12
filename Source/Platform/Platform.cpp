#include "misc.h"

namespace Platform {

  std::set<Event::Listener*>& EventSet() {
    static std::set<Event::Listener*> set;
    return set;
  }

  Event::Listener::Listener() {
    EventSet().insert(this);
  }

  Event::Listener::~Listener() {
    EventSet().erase(this);
  }

}