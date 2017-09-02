#include "Log.h"

#include <assert.h>
#include <iostream>

namespace Core {
  Log::Log() {
    system("Color");
  }

  Log::LogObserver::LogObserver(const Flag_& flags) {
    SetFlags(flags);
  }

  void Log::LogObserver::Print(const std::string& message, const Flag_& flags) {
    if (CheckFlags(flags, true)) {
      const Flag_ flags_ = GetFlags();
      if (flags & MESSAGE)  PrintMessage(message);
      if (flags & SUCCESS)  PrintMessage(message);
      if (flags & WARNING)  PrintMessage(message);
      if (flags & ERROR  )  PrintMessage(message);
      if (flags & ASSERT )  PrintMessage(message);
      if (flags & BREAK  )  PrintMessage(message);
    }
  }

  void Log::Print(const std::string& message, const Flag_& logTargets) {
    NOTIFY_OBSERVERS(LogObserver, Print(message, logTargets));
  }

  void Log::PrintMessage(const std::string& message, const Flag_& logTargets) {
    Print(message, MESSAGE & logTargets);
  }

  void Log::PrintSuccess(const std::string& message, const Flag_& logTargets) {
    Print(message, SUCCESS & logTargets);
  }

  void Log::PrintWarning(const std::string& message, const Flag_& logTargets) {
    Print(message, WARNING & logTargets);
  }

  void Log::PrintError(const std::string& message, const Flag_& logTargets) {
    Print(message, ERROR & logTargets);
  }

  void Log::PrintAssert(bool condition, const std::string& message, const Flag_& logTargets) {
    if (!condition) {
      Print(message, ASSERT & logTargets);
      assert(false);
    }
  }

  void Log::PrintBreak(const Flag_& logTargets) {
    Print("", BREAK);
  }

  /*void Log::Print(const std::string& message, unsigned int colour) {
    std::cout << "\033[1;" << colour << "m" << message << "\033[0m" << std::endl;
  }*/
}