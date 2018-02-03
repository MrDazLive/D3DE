#include <Core/Command.h>
#include <Core/ExamBoard.h>

#include "declerations.h"

#define EXAMBOARD         Core::ExamBoard::Instance("Platform_Tests")
#define EXAMINATION(T)    EXAMBOARD->Examine<T>();

using namespace Platform_Test;

int main(int argc, char **args) {

  Core::Command::Collect(argc, args);
  
  if(Core::Command::Check("-demo")) {
    return DemoMode();
  } else {
    EXAMINATION(Window);
    EXAMINATION(Input);
    return EXAMBOARD->Results() ? 0 : 1;
  }
}