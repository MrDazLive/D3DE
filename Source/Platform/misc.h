#include "Platform.h"
#include <set>
#include <functional>

namespace Platform {

  std::set<Event::Listener*>& EventSet();

  template <typename F, typename ... V>
  void SignalEvent(F function, V... args) {
    auto func = std::bind(function, std::placeholders::_1, args...);
    for(auto ptr : EventSet()) {
      func(ptr);
    }
  }

}