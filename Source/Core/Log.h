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
    typedef Flag16 Flag_;

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

      LOW       = FLAG(6),
      MEDIUM    = FLAG(7),
      HIGH      = FLAG(8),

      UNIT_TEST = FLAG(15)
    };

    static Flag_        s_logMessages;
    static Flag_        s_logPriorities;
    static Flag_        s_logTargets;
    
    /// <summary>
    /// Logs the provided message according to the provided log type.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify how the message is distributed.</param>
    void  Print         (const std::string&, const Flag_& = Flag::MESSAGE | Log::MEDIUM | s_logTargets);

    /// <summary>
    /// Logs the provided message.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintMessage  (const std::string&, const Flag_& = Log::MEDIUM | s_logTargets);

    /// <summary>
    /// Logs the provided message as in the "success" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintSuccess  (const std::string&, const Flag_& = Log::MEDIUM | s_logTargets);

    /// <summary>
    /// Logs the provided message as in the "warning" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintWarning  (const std::string&, const Flag_& = Log::MEDIUM | s_logTargets);

    /// <summary>
    /// Logs the provided message as in the "error" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintError    (const std::string&, const Flag_& = Log::MEDIUM | s_logTargets);

    /// <summary>
    /// Checks assert condition, logging an arror message if assert fails.
    /// </summary>
    /// <param name = "condition">The assert condition.</param>
    /// <param name = "message">The error message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintAssert   (bool, const std::string& = "", const Flag_& = Log::MEDIUM | s_logTargets);

    /// <summary>
    /// Prints a break line into the log.
    /// </summary>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message break.</param>
    void  PrintBreak    (const Flag_& = Log::MEDIUM | s_logTargets);
  protected:
          /// <summary>
          /// Default constructor.
          /// </summary>
          Log           ();
  };

  /// <summary>
  /// Base class used to distribute log messages.
  /// </summary>
  OBSERVER_CLASS(Log), public Flags<Log::Flag_> {
  public:
                  Observer      (const Log::Flag_& flags = Log::Flag_(~Log::UNIT_TEST));

            void  Print         (const std::string&, const Log::Flag_&);
  protected:
    virtual void  PrintMessage  (const std::string&) {}
    virtual void  PrintSuccess  (const std::string&) {}
    virtual void  PrintWarning  (const std::string&) {}
    virtual void  PrintError    (const std::string&) {}
    virtual void  PrintAssert   (const std::string&) {}
    virtual void  PrintBreak    (                  ) {}
  };

  #define LOG Core::Log::Instance()
}