#include <Core\ExamBoard.h>

#include "declerations.h"

#define EXAMBOARD Core::ExamBoard::Instance("Core_Tests")

using namespace Core_Test;

int main() {
  EXAMBOARD->Examine<String>();
  EXAMBOARD->Examine<Handler>();
  EXAMBOARD->Examine<File>();
  EXAMBOARD->Results();
  return 0;
}