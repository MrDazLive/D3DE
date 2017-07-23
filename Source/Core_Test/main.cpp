#include <Core\ExamBoard.h>

#include "StringUtil_test.h"

#define EXAMBOARD Core::ExamBoard::Instance("Core_Tests")

using namespace Core_Test;

int main() {
  EXAMBOARD->Examine<String>();
  EXAMBOARD->Results();
  return 0;
}