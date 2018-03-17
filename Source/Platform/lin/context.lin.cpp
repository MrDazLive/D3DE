#ifdef __linux__

#include "context.lin.h"

std::map<int, DisplayContext>& ContextMap() {
  static std::map<int, DisplayContext> map;
  return map;
}

DisplayContext* const GetContext(int idx) {
  auto it = ContextMap().find(idx);
  return it != ContextMap().end() ? &(it->second) : nullptr;
}

#endif