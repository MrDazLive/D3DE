#include "Log.h"

#include "ConsoleLog.h"

#include <assert.h>

namespace Core {
  Log::Log() {
    AddObserver(ConsoleLog::Instance());
  }

  std::set<Observable<Log>::Observer*> Observable<Log>::s_globalObservers = {};

  inline void Observable<Log>::Observer::Print(const std::string& message, const Log::Flag_& flags) {
    if (CheckFlags(flags, true)) {
      const Log::Flag_ flags_ = GetFlags();
      if (flags & Log::MESSAGE)  PrintMessage (message);
      if (flags & Log::SUCCESS)  PrintSuccess (message);
      if (flags & Log::WARNING)  PrintWarning (message);
      if (flags & Log::ERROR  )  PrintError   (message);
      if (flags & Log::ASSERT )  PrintAssert  (message);
      if (flags & Log::BREAK  )  PrintBreak   (       );
    }
  }

  void Log::Print(const std::string& message, const Flag_& logTargets) {
    NOTIFY_OBSERVERS(Print(message, logTargets));
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
}