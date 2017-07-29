#pragma once

#include <string>
#include "Singleton.h"

namespace Core {

  /// <summary>
  /// Class used for logging information for debug purposes.
  /// </summary>
  class Log : public Singleton<Log> {
    friend Singleton;
  public:
    /// <summary>
    /// Enumerator used to identify the type of debug message desired for printing.
    /// </summary>
    enum Type {
      MESSAGE,
      SUCCESS,
      WARNING,
      ERROR,
      ASSERT
    };

    /// <summary>
    /// Logs the provided message according to the provided log type.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logType">The identifier used to for specify how the message is logged.</param>
    void  Debug         (const std::string&, const Type = WARNING);

    /// <summary>
    /// Logs the provided message.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  DebugMessage  (const std::string&);

    /// <summary>
    /// Logs the provided message as in the "success" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  DebugSuccess  (const std::string&);

    /// <summary>
    /// Logs the provided message as in the "warning" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  DebugWarning  (const std::string&);

    /// <summary>
    /// Logs the provided message as in the "error" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  DebugError    (const std::string&);

    /// <summary>
    /// Checks assert condition, logging an arror message if assert fails.
    /// </summary>
    /// <param name = "condition">The assert condition.</param>
    /// <param name = "message">The error message to be logged.</param>
    void  DebugAssert   (bool, const std::string& = "");

    /// <summary>
    /// Prints a break line into the log.
    /// </summary>
    void  DebugBreak    ();
  protected:
          /// <summary>
          /// Default constructor.
          /// </summary>
          Log           ();
  private:
    /// <summary>
    /// Prints the provided message using the provided colour code.
    /// </summary>
    /// <param = "message">The message to be printed to the console.</param>
    /// <param = "colour">The value used for specifying the print colour.</param>
    void  Print         (const std::string&, unsigned int);
  };

  #define LOG Log::Instance()
}