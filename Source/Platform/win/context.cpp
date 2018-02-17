#ifdef _WIN32

#include "context.h"

std::map<int, DisplayContext>& ContextMap() {
  static std::map<int, DisplayContext> map;
  return map;
}

DisplayContext* const GetContext(int idx) {
  auto it = ContextMap().find(idx);
  return it != ContextMap().end() ? &(it->second) : nullptr;
}

int GetContext(const DisplayContext& ctx) {
  auto map = ContextMap();
  for (auto it : map) {
    if (it.second == ctx)
      return it.first;
  }
  return -1;
}

#endif