#include <Core/Command.h>
#include <Core/ExamBoard.h>

#include "declerations.h"

#define EXAMBOARD         Core::ExamBoard::Instance("Type_Tests")
#define EXAMINATION(T)    EXAMBOARD->Examine<T>();

using namespace Types_Test;

int main(int argc, char **args) {

  Core::Command::Collect(argc, args);

  EXAMINATION(String);
  return EXAMBOARD->Results() ? 0 : 1;
}