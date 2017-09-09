#pragma once

#include <string>

#include "Flags.h"
#include "Observer.h"
#include "Singleton.h"

namespace Core {

  /// <summary>
  /// Class used for logging information for debug purposes.
  /// </summary>
  class Log :
    public Singleton<Log>,
    public Observable<Log> {
    friend Singleton;
  public:
    typedef Flag8 Flag_;

    /// <summary>
    /// Enumerator used for identifying the message type.
    /// </summary>
    enum Flag {
      MESSAGE   = FLAG(0),
      SUCCESS   = FLAG(1),
      WARNING   = FLAG(2),
      ERROR     = FLAG(3),
      ASSERT    = FLAG(4),
      BREAK     = FLAG(5),

      UNIT_TEST = FLAG(7)
    };
#define LOG_MESSAGES  (Log::MESSAGE | Log::SUCCESS | Log::WARNING | Log::ERROR | Log::ASSERT | Log::BREAK) 
#define LOG_TARGETS   ~LOG_MESSAGES & !Log::UNIT_TEST

    /// <summary>
    /// Base class used to distribute log messages.
    /// </summary>
    class Observer : public Flags<Flag_>, public ObserverBase<Log> {
    public:
                    Observer      (const Flag_& = ~UNIT_TEST);

      void          Print         (const std::string&, const Flag_&);
    protected:
      virtual void  PrintMessage  (const std::string&) {}
      virtual void  PrintSuccess  (const std::string&) {}
      virtual void  PrintWarning  (const std::string&) {}
      virtual void  PrintError    (const std::string&) {}
      virtual void  PrintAssert   (const std::string&) {}
      virtual void  PrintBreak    (                  ) {}
    };

    /// <summary>
    /// Logs the provided message according to the provided log type.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logType">The identifier used to for specify how the message is logged.</param>
    void  Print         (const std::string&, const Flag_& = Flag::WARNING & LOG_TARGETS);

    /// <summary>
    /// Logs the provided message.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  PrintMessage  (const std::string&, const Flag_& = LOG_TARGETS);

    /// <summary>
    /// Logs the provided message as in the "success" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  PrintSuccess  (const std::string&, const Flag_& = LOG_TARGETS);

    /// <summary>
    /// Logs the provided message as in the "warning" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  PrintWarning  (const std::string&, const Flag_& = LOG_TARGETS);

    /// <summary>
    /// Logs the provided message as in the "error" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    void  PrintError    (const std::string&, const Flag_& = LOG_TARGETS);

    /// <summary>
    /// Checks assert condition, logging an arror message if assert fails.
    /// </summary>
    /// <param name = "condition">The assert condition.</param>
    /// <param name = "message">The error message to be logged.</param>
    void  PrintAssert   (bool, const std::string& = "", const Flag_& = LOG_TARGETS);

    /// <summary>
    /// Prints a break line into the log.
    /// </summary>
    void  PrintBreak    (const Flag_& = LOG_TARGETS);
  protected:
          /// <summary>
          /// Default constructor.
          /// </summary>
          Log           ();
  };

  #define LOG Log::Instance()
}