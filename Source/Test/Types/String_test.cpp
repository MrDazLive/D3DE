#include "declerations.h"

#include <Types/String.h>

namespace Types_Test {
  void String::Reset() {}

  void String::Examine() {
    TestCase([]() {
      DTU::String s;
      return s.size() == 0;
    }, "String()");

    TestCase([]() {
      DTU::String s("word");
      return s == "word";
    }, "String(const char*)");

    TestCase([]() {
      std::string w("word");
      DTU::String s(w);
      return s == "word";
    }, "String(const std::string&)");

    TestCase([]() {
      DTU::String w("word");
      DTU::String s(w);
      return s == "word";
    }, "String(const DTU::String&)");

    TestCase([]() {
      DTU::String s("word");
      return s[1] == 'o';
    }, "String[]");

    TestCase([]() {
      DTU::String s("word");
      const char* w("word");
      return s == w;
    }, "String==(const char*)");

    TestCase([]() {
      DTU::String s("word");
      std::string w("word");
      return s == w;
    }, "String==(const std::string&)");

    TestCase([]() {
      DTU::String s("word");
      DTU::String w("word");
      return s == w;
    }, "String==(const DTU::String&)");

    TestCase([]() {
      DTU::String s("word");
      const char* w("words");
      return s != w;
    }, "String!=(const char*)");

    TestCase([]() {
      DTU::String s("word");
      std::string w("words");
      return s != w;
    }, "String!=(const std::string&)");

    TestCase([]() {
      DTU::String s("word");
      DTU::String w("words");
      return s != w;
    }, "String!=(const DTU::String&)");

    TestCase([](){
      DTU::String s("word");
      s = s + "s";
      return s == "words";
    }, "String+");

    TestCase([](){
      DTU::String s("word");
      s += "s";
      return s == "words";
    }, "String+=");

    TestCase([]() {
      DTU::String s("word");
      return s.size() == 4;
    }, "String::size");
  }
}