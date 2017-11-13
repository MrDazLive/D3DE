#include "Log.h"

#include "FileLog.h"
#include "ConsoleLog.h"

#include <assert.h>

namespace Core {

  Log::Flag_ Log::s_logTypes = Log::MESSAGE | Log::SUCCESS | Log::WARNING | Log::ERROR | Log::ASSERT | Log::BREAK;
  Log::Flag_ Log::s_logPriorities = Log::LOW | Log::MEDIUM | Log::HIGH;
  Log::Flag_ Log::s_logTargets = ~(s_logTargets | s_logPriorities) & !Log::UNIT_TEST;

  Log::Log() {
    AddObserver(FileLog::Instance());
    AddObserver(ConsoleLog::Instance());
  }

  void Log::Print(const DTU::String& message, const Flag_& logFlags) {
    if(logFlags & s_logPriorities == 0)
      NotifyObservers(&Observer::Print, message, logFlags | Log::MEDIUM);
    else
      NotifyObservers(&Observer::Print, message, logFlags);
  }

  void Log::PrintMessage(const DTU::String& message, const Flag_& logFlags) {
    Print(message, MESSAGE | logFlags);
  }

  void Log::PrintSuccess(const DTU::String& message, const Flag_& logFlags) {
    Print(message, SUCCESS | logFlags);
  }

  void Log::PrintWarning(const DTU::String& message, const Flag_& logFlags) {
    Print(message, WARNING | logFlags);
  }

  void Log::PrintError(const DTU::String& message, const Flag_& logFlags) {
    Print(message, ERROR | logFlags);
  }

  void Log::PrintAssert(bool condition, const DTU::String& message, const Flag_& logFlags) {
    if (!condition) {
      Print(message, ASSERT | logFlags);
      assert(false);
    }
  }

  void Log::PrintBreak(const Flag_& logFlags) {
    Print("", BREAK);
  }

  template <>
  std::set<Observable<Log>::Observer*> Observable<Log>::s_globalObservers = {};

  Log::Observer::Observer(const Log::Flag_& logFlags) {
    SetFlags(logFlags);
  }

  void Log::Observer::Print(const DTU::String& message, const Log::Flag_& logFlags) {
    if (CheckFlags(logFlags, true)) {
      const Log::Flag_ flags_ = GetFlags();
      if (logFlags & Log::MESSAGE) PrintMessage(message);
      if (logFlags & Log::SUCCESS) PrintSuccess(message);
      if (logFlags & Log::WARNING) PrintWarning(message);
      if (logFlags & Log::ERROR  ) PrintError  (message);
      if (logFlags & Log::ASSERT ) PrintAssert (message);
      if (logFlags & Log::BREAK  ) PrintBreak  (       );
    }
  }

}