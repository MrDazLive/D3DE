#include <Core\ExamBoard.h>

#define Examination Core::ExamBoard::Instance("Core_Tests")

int main() {
  Examination->Results();
  return 0;
}