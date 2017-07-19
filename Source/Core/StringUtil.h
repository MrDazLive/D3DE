#pragma once

#include <string>

namespace Core {
  namespace String {

    template <typename ... V>
    std::string Format(const char* text, V... args) {
      char buffer[1024];
      sprintf_s(buffer, text, args...);
      return std::string(buffer);
    }

  }
}