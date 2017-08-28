#include "declerations.h"

#include <Core\StringUtil.h>

using namespace Core::String;

namespace Core_Test {
  void String::Reset() {}

  void String::Examine() {
    TestCase([]() {
      return Compare(std::string("test text"), "test text");
    }, "String::Compare");

    TestCase([]() {
      return !Compare(std::string("test text"), "Test Text");
    }, "String::Compare");

    TestCase([]() {
      std::string text = Format("%i is an interger and %.3f is a float.", 3, 0.142f);
      return Compare(text, "3 is an interger and 0.142 is a float.");
    }, "String::Format");
  }
}