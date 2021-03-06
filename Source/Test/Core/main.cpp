#include <Core/Command.h>
#include <Core/ExamBoard.h>

#include "declerations.h"

#define EXAMBOARD         Core::ExamBoard::Instance("Core_Tests")
#define EXAMINATION(T)    EXAMBOARD->Examine<T>();

using namespace Core_Test;

int main(int argc, char **args) {

  Core::Command::Collect(argc, args);

  EXAMINATION(Handler);
  EXAMINATION(File);
  EXAMINATION(Flags);
  EXAMINATION(Observer);
  EXAMINATION(System)
  return EXAMBOARD->Results() ? 0 : 1;
}