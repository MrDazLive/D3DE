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
      const char* w("WoRd");
      return s != w;
    }, "String!=(const char*)");

    TestCase([]() {
      DTU::String s("word");
      std::string w("WoRd");
      return s != w;
    }, "String!=(const std::string&)");

    TestCase([]() {
      DTU::String s("word");
      DTU::String w("WoRd");
      return s != w;
    }, "String!=(const DTU::String&)");

    TestCase([]() {
      DTU::String s("word");
      s = s + "s";
      return s == "words";
    }, "String+");

    TestCase([]() {
      DTU::String s("word");
      s = "words";
      return s == "words";
    }, "String=");

    TestCase([]() {
      DTU::String s("word");
      s += "s";
      return s == "words";
    }, "String+=");

    TestCase([]() {
      DTU::String s("word");
      return s.size() == 4;
    }, "String::size");

    TestCase([]() {
      DTU::String s("WoRd");
      return s.upper() == "WORD"
        && s == "WoRd";
    }, "String::upper");

    TestCase([]() {
      DTU::String s("WoRd");
      return s.lower() == "word"
        && s == "WoRd";
    }, "String::lower");

    TestCase([]() {
      DTU::String s("WoRd");
      s.toUpper();
      return s == "WORD";
    }, "String::toUpper");

    TestCase([]() {
      DTU::String s("WoRd");
      s.toLower();
      return s.toLower() == "word";
    }, "String::toLower");

    TestCase([]() {
      DTU::String s("%s is %.2f.");
      s.format("Pi", "Pi", 3.142f);
      return s == "Pi is 3.14.";
    }, "String::format");

    TestCase([]() {
      return DTU::String::Format("%s is %.2f.", "Pi", 3.142f) == "Pi is 3.14.";
    }, "String::Format");

    TestCase([]() {
      DTU::String s("\\https://www.google.com");
      return s.startsWith("\\/");
    }, "String::startsWith");

    TestCase([]() {
      DTU::String s("https://www.google.com");
      return s.startsWithText("https://");
    }, "String::startsWithText");

    TestCase([]() {
      DTU::String s("https://www.google.com/");
      return s.endsWith("\\/");
    }, "String::endsWith");

    TestCase([]() {
      DTU::String s("https://www.google.com");
      return s.endsWithText(".com");
    }, "String::endsWithText");
  }
}