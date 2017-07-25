#include <Core\ExamBoard.h>
#include <Core\Handler.h>

#include "StringUtil_test.h"
#include "Handler_test.h"

#define EXAMBOARD Core::ExamBoard::Instance("Core_Tests")

using namespace Core_Test;

int main() {
  EXAMBOARD->Examine<String>();
  EXAMBOARD->Examine<Handler>();
  EXAMBOARD->Results();
  return 0;
}