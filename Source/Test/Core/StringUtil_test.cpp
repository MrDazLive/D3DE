#include "declerations.h"

#include <Core/StringUtil.h>

using namespace Core::String;

namespace Core_Test {
  void String::Reset() {}

  void String::Examine() {
    TestCase([]() {
      return Equals(std::string("test text"), "test text");
    }, "String::Equals");

    TestCase([]() {
      return !Equals(std::string("test text"), "Test Text");
    }, "String::Equals");

    TestCase([]() {
      std::string text = Format("%i is an interger and %.3f is a float.", 3, 0.142f);
      return Equals(text, "3 is an interger and 0.142 is a float.");
    }, "String::Format");

    TestCase([]() {
      std::string text_a = "text\\";
      std::string text_b = "text/";
      std::string text_c = "text-";
      return EndsWith(text_a, "\\") && EndsWith(text_b, "\\/") && !EndsWith(text_c, "+");
    }, "String::EndsWith");
  }
}