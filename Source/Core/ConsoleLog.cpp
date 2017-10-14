#include "ConsoleLog.h"

#include <iostream>

namespace Core {

  ConsoleLog::ConsoleLog() : Log::Observer(~Log::Flag_(0)) {
    system("color");
  }

  void ConsoleLog::PrintMessage(const DTU::String& message) {
    Log(message, 37);
  }

  void ConsoleLog::PrintSuccess(const DTU::String& message) {
    Log(message, 32);
  }

  void ConsoleLog::PrintWarning(const DTU::String& message) {
    Log(message, 33);
  }

  void ConsoleLog::PrintError(const DTU::String& message) {
    Log(message, 31);
  }

  void ConsoleLog::PrintAssert(const DTU::String& message) {
    Log(message, 35);
  }

  void ConsoleLog::PrintBreak() {
    std::cout << std::endl;
  }

  void ConsoleLog::Log(const DTU::String& message, const unsigned int colour) {
    std::cout << "\033[1;" << colour << "m" << message.c_str() << "\033[0m" << std::endl;
  }

}