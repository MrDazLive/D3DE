#pragma once

#include <string>
#include "Singleton.h"

namespace Core {
  class Log : public Singleton<Log> {
    friend Singleton;
  public:
    void DebugMessage(const std::string&);
    void DebugSuccess(const std::string&);
    void DebugWarning(const std::string&);
    void DebugError(const std::string&);
  protected:
    Log();
  private:
    void Print(const std::string&, unsigned int);
  };

  #define Logger Log::Instance()
}