#pragma once

#include "Log.h"
#include "Singleton.h"

namespace Core {
  class ConsoleLog : public Singleton<ConsoleLog>, public Log::Observer {
    friend Singleton;
  protected:
          ConsoleLog    ();

    void  PrintMessage  (const DTU::String&) final override;
    void  PrintSuccess  (const DTU::String&) final override;
    void  PrintWarning  (const DTU::String&) final override;
    void  PrintError    (const DTU::String&) final override;
    void  PrintAssert   (const DTU::String&) final override;
    void  PrintBreak    (                  ) final override;
  private:
    /// <summary>
    /// Prints the provided message to the console using the provided colour code.
    /// </summary>
    /// <param = "message">The message to be printed to the console.</param>
    /// <param = "colour">The value used for specifying the print colour.</param>
    void  Log           (const DTU::String&, const unsigned int);
  };
}