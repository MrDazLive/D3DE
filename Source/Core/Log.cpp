#include "Log.h"

#include "FileLog.h"
#include "ConsoleLog.h"

#include <assert.h>

namespace Core {

  Log::Flags Log::s_logTypes    = Log::MESSAGE | Log::SUCCESS | Log::WARNING | Log::ERROR | Log::ASSERT | Log::BREAK;
  Log::Flags Log::s_logTargets  = ~(s_logTargets) & !Log::UNIT_TEST;

  Log::Log() {
    AddObserver(FileLog::Instance());
    AddObserver(ConsoleLog::Instance());
  }

  void Log::Print(const DTU::String& message, const Flags& logFlags) {
    NotifyObservers(&Observer::Print, message, logFlags);
  }

  void Log::PrintMessage(const DTU::String& message, const Flags& logFlags) {
    Print(message, MESSAGE | logFlags);
  }

  void Log::PrintSuccess(const DTU::String& message, const Flags& logFlags) {
    Print(message, SUCCESS | logFlags);
  }

  void Log::PrintWarning(const DTU::String& message, const Flags& logFlags) {
    Print(message, WARNING | logFlags);
  }

  void Log::PrintError(const DTU::String& message, const Flags& logFlags) {
    Print(message, ERROR | logFlags);
  }

  void Log::PrintAssert(bool condition, const DTU::String& message, const Flags& logFlags) {
    if (!condition) {
      Print(message, ASSERT | logFlags);
      assert(false);
    }
  }

  void Log::PrintBreak(const Flags& logFlags) {
    Print("", BREAK);
  }

  Log::Observer::Observer(const Log::Flags& logFlags) {
    SetFlags(logFlags);
  }

  void Log::Observer::Print(const DTU::String& message, const Log::Flags& logFlags) {
    if (CheckFlags(logFlags, true)) {
      const Log::Flags flags_ = GetFlags();
      if (logFlags & Log::MESSAGE) PrintMessage(message);
      if (logFlags & Log::SUCCESS) PrintSuccess(message);
      if (logFlags & Log::WARNING) PrintWarning(message);
      if (logFlags & Log::ERROR  ) PrintError  (message);
      if (logFlags & Log::ASSERT ) PrintAssert (message);
      if (logFlags & Log::BREAK  ) PrintBreak  (       );
    }
  }

}