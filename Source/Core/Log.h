#pragma once

#include "Flags.h"
#include "Observer.h"
#include "Singleton.h"

#include <Types/String.h>

namespace Core {

  /// <summary>
  /// Class used for logging information for debug purposes.
  /// </summary>
  class Log :
    public Singleton<Log>,
    public Observable<Log> {
    friend Singleton;
  public:
    typedef Flag16 Flags;

    /// <summary>
    /// Enumerator used for identifying the message type.
    /// </summary>
    enum Flag : Flags {
      MESSAGE   = FLAG(0),
      SUCCESS   = FLAG(1),
      WARNING   = FLAG(2),
      ERROR     = FLAG(3),
      ASSERT    = FLAG(4),
      BREAK     = FLAG(5),

      UNIT_TEST = FLAG(15)
    };

    static Flags        s_logTypes;
    static Flags        s_logTargets;
    
    /// <summary>
    /// Logs the provided message according to the provided log type.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify how the message is distributed.</param>
    void  Print         (const DTU::String&, const Flags& = Flag::MESSAGE | s_logTargets);

    /// <summary>
    /// Logs the provided message.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintMessage  (const DTU::String&, const Flags& = s_logTargets);

    /// <summary>
    /// Logs the provided message as in the "success" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintSuccess  (const DTU::String&, const Flags& = s_logTargets);

    /// <summary>
    /// Logs the provided message as in the "warning" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintWarning  (const DTU::String&, const Flags& = s_logTargets);

    /// <summary>
    /// Logs the provided message as in the "error" formatting.
    /// </summary>
    /// <param name = "message">The message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintError    (const DTU::String&, const Flags& = s_logTargets);

    /// <summary>
    /// Checks assert condition, logging an arror message if assert fails.
    /// </summary>
    /// <param name = "condition">The assert condition.</param>
    /// <param name = "message">The error message to be logged.</param>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message.</param>
    void  PrintAssert   (bool, const DTU::String& = "", const Flags& = s_logTargets);

    /// <summary>
    /// Prints a break line into the log.
    /// </summary>
    /// <param name = "logTargets">The flags used to specify the targets for distributing the message break.</param>
    void  PrintBreak    (const Flags& = s_logTargets);
  protected:
          /// <summary>
          /// Default constructor.
          /// </summary>
          Log           ();
  };

  /// <summary>
  /// Base class used to distribute log messages.
  /// </summary>
  OBSERVER_CLASS(Log), public Flags<Log::Flags> {
  public:
                  Observer      (const Log::Flags& flags = Log::Flags(~Log::UNIT_TEST));

            void  Print         (const DTU::String&, const Log::Flags&);
  protected:
    virtual void  PrintMessage  (const DTU::String&) {}
    virtual void  PrintSuccess  (const DTU::String&) {}
    virtual void  PrintWarning  (const DTU::String&) {}
    virtual void  PrintError    (const DTU::String&) {}
    virtual void  PrintAssert   (const DTU::String&) {}
    virtual void  PrintBreak    (                  ) {}
  };

  #define LOG Core::Log::Instance()
}