#include "ConsoleLog.h"

#include <iostream>

namespace Core {

  ConsoleLog::ConsoleLog() : Log::Observer(~Log::Flag_(0)) {
    system("color");
  }

  void ConsoleLog::PrintMessage(const std::string& message) {
    Log(message, 37);
  }

  void ConsoleLog::PrintSuccess(const std::string& message) {
    Log(message, 32);
  }

  void ConsoleLog::PrintWarning(const std::string& message) {
    Log(message, 33);
  }

  void ConsoleLog::PrintError(const std::string& message) {
    Log(message, 31);
  }

  void ConsoleLog::PrintAssert(const std::string& message) {
    Log(message, 35);
  }

  void ConsoleLog::PrintBreak() {
    std::cout << std::endl;
  }

  void ConsoleLog::Log(const std::string& message, const unsigned int colour) {
    std::cout << "\033[1;" << colour << "m" << message << "\033[0m" << std::endl;
  }

}