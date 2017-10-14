#include "Log.h"

#include "FileLog.h"
#include "ConsoleLog.h"

#include <assert.h>

namespace Core {

  Log::Flag_ Log::s_logMessages = Log::MESSAGE | Log::SUCCESS | Log::WARNING | Log::ERROR | Log::ASSERT | Log::BREAK;
  Log::Flag_ Log::s_logPriorities = Log::LOW | Log::MEDIUM | Log::HIGH;
  Log::Flag_ Log::s_logTargets = ~(s_logTargets | s_logPriorities) & !Log::UNIT_TEST;

  Log::Log() {
    AddObserver(FileLog::Instance());
    AddObserver(ConsoleLog::Instance());
  }

  void Log::Print(const DTU::String& message, const Flag_& logTargets) {
    NOTIFY_OBSERVERS(Print(message, logTargets));
  }

  void Log::PrintMessage(const DTU::String& message, const Flag_& logTargets) {
    Print(message, MESSAGE | logTargets);
  }

  void Log::PrintSuccess(const DTU::String& message, const Flag_& logTargets) {
    Print(message, SUCCESS | logTargets);
  }

  void Log::PrintWarning(const DTU::String& message, const Flag_& logTargets) {
    Print(message, WARNING | logTargets);
  }

  void Log::PrintError(const DTU::String& message, const Flag_& logTargets) {
    Print(message, ERROR | logTargets);
  }

  void Log::PrintAssert(bool condition, const DTU::String& message, const Flag_& logTargets) {
    if (!condition) {
      Print(message, ASSERT | logTargets);
      assert(false);
    }
  }

  void Log::PrintBreak(const Flag_& logTargets) {
    Print("", BREAK);
  }

  template <>
  std::set<Observable<Log>::Observer*> Observable<Log>::s_globalObservers = {};

  Log::Observer::Observer(const Log::Flag_& flags) {
    SetFlags(flags);
  }

  void Log::Observer::Print(const DTU::String& message, const Log::Flag_& flags) {
    if (CheckFlags(flags, true)) {
      const Log::Flag_ flags_ = GetFlags();
      if (flags & Log::MESSAGE) PrintMessage(message);
      if (flags & Log::SUCCESS) PrintSuccess(message);
      if (flags & Log::WARNING) PrintWarning(message);
      if (flags & Log::ERROR  ) PrintError  (message);
      if (flags & Log::ASSERT ) PrintAssert (message);
      if (flags & Log::BREAK  ) PrintBreak  (       );
    }
  }

}