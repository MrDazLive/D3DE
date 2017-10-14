#include "Command.h"

#include "Log.h"

namespace Core {

  std::set<DTU::String> Command::s_commands;

  void Command::Collect(const int argc, char** const args) {
    for (int idx = 0; idx < argc; ++idx) {
      s_commands.emplace(args[idx]);
    }
  }

  const DTU::String& Command::Fetch(const int index) {
    LOG->PrintAssert(index < s_commands.size(), "Command index out of bounds.");
    return *(std::next(s_commands.begin(), index));
  }

  bool Command::Check(const DTU::String& command) {
    return s_commands.find(command) != s_commands.end();
  }

}