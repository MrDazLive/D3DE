#include "StringUtil_test.h"

#include <Core\StringUtil.h>

using namespace Core::String;

namespace Core_Test {
  String::String() : UnitTest("String Utilities") {}

  void String::Examine() {
    TestCase([]() {
      std::string text = Format("%i is an interger and %.3f is a float.", 3, 0.142f);
      return text.compare("3 is an interger and 0.142 is a float.") == 0;
    });
  }
}