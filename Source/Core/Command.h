#pragma once

#include <Types/String.h>
#include <set>

namespace Core {

  /// <summary>
  /// Static class for holding command line arguments.
  /// </summary>
  class Command {
  public:
    /// <summary>
    /// <i>Static funciton.</i><br/>
    /// Inserts provided command line arguments to set.
    /// </summary>
    static void                   Collect     (const int, char** const);

    /// <summary>
    /// <i>Static funciton.</i><br/>
    /// Fetches the command argument from the provided index.
    /// </summary>
    static const DTU::String&     Fetch       (const int);

    /// <summary>
    /// <i>Static funciton.</i><br/>
    /// Checks that the provided command argument exists.
    /// </summary>
    static bool                   Check       (const DTU::String&);
  private:
                                  /// <summary>
                                  /// Delete constructor.
                                  /// </summary>
                                  Command     () = delete;

                                  /// <summary>
                                  /// Delete destructor.
                                  /// </summary>
                                  ~Command    () = delete;

    static std::set<DTU::String>  s_commands;
  };

}