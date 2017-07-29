#include "Log.h"

#include <assert.h>
#include <iostream>

namespace Core {
  Log::Log() {
    system("Color");
  }

  void Log::Debug(const std::string& message, const Type logType) {
    switch (logType) {
    case MESSAGE: DebugMessage(message);        break;
    case SUCCESS: DebugSuccess(message);        break;
    case WARNING: DebugWarning(message);        break;
    case ASSERT:  DebugAssert (false, message); break;
    default:      DebugError  (message);        break;
    }
  }

  void Log::DebugMessage(const std::string& message) {
    Print(message, 37);
  }

  void Log::DebugSuccess(const std::string& message) {
    Print(message, 32);
  }

  void Log::DebugWarning(const std::string& message) {
    Print(message, 33);
  }

  void Log::DebugError(const std::string& message) {
    Print(message, 31);
  }

  void Log::DebugAssert(bool condition, const std::string& message) {
    if (!condition) {
      Print("Assert thrown: " + message, 35);
      assert(false);
    }
  }

  void Log::DebugBreak() {
    std::cout << std::endl;
  }

  void Log::Print(const std::string& message, unsigned int colour) {
    std::cout << "\033[1;" << colour << "m" << message << "\033[0m" << std::endl;
  }
}