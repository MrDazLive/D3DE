#pragma once

#include "Log.h"
#include "Singleton.h"

namespace Core {
  class ConsoleLog : public Singleton<ConsoleLog>, public Log::Observer {
  public:
    ConsoleLog();
  protected:
    void  PrintMessage  (const std::string&) final override;
    void  PrintSuccess  (const std::string&) final override;
    void  PrintWarning  (const std::string&) final override;
    void  PrintError    (const std::string&) final override;
    void  PrintAssert   (const std::string&) final override;
    void  PrintBreak    (                  ) final override;
  private:
    /// <summary>
    /// Prints the provided message to the console using the provided colour code.
    /// </summary>
    /// <param = "message">The message to be printed to the console.</param>
    /// <param = "colour">The value used for specifying the print colour.</param>
    void  Log           (const std::string&, const unsigned int);
  };
}