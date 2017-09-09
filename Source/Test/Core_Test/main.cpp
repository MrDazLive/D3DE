#include <Core\ExamBoard.h>

#include "declerations.h"

#define EXAMBOARD         Core::ExamBoard::Instance("Core_Tests")
#define EXAMINATION(T)    EXAMBOARD->Examine<T>();

using namespace Core_Test;

int main() {
  EXAMINATION(String);
  EXAMINATION(Handler);
  EXAMINATION(File);
  EXAMINATION(Flags);
  EXAMINATION(Observer);
  EXAMBOARD->Results();
  return 0;
}