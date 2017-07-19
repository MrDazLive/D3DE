#include "Log.h"

#include <iostream>

namespace Core {
  Log::Log() {
    system("Color");
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

  void Log::Print(const std::string& message, unsigned int colour) {
    std::cout << "\033[" << colour << "m" << message << std::endl;
  }
}