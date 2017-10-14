#include "declerations.h"

#include <Core/File.h>

Core::File test_file("File/File2/test.txt");

namespace Core_Test {
  void File::Reset() {
    test_file.Delete();
  }

  void File::Examine() {
    TestCase([]() {
      return !test_file.Exists();
    }, "File::Exists");

    TestCase([]() {
      return test_file.Create() && test_file.Exists();
    }, "File::Create");

    TestCase([]() {
      return test_file.Create() && test_file.Create(true) && test_file.Exists();
    }, "File::Create(true)");

    TestCase([]() {
      return test_file.Create() && !test_file.Create() && test_file.Exists();
    }, "File::Create(false)");

    TestCase([]() {
      return test_file.Create() && test_file.Delete() && !test_file.Exists();
    }, "File::Delete");

    TestCase([]() {
      return test_file.Create() && test_file.isOpen();
    }, "File::isOpen");

    TestCase([]() {
      return test_file.Create() && test_file.isEmpty();
    }, "File::isEmpty");

    TestCase([]() {
      test_file.Create();
      test_file.InsertLine("LineA");
      test_file.InsertLine("LineB");
      DTU::String content;
      test_file.getContent(content, true);
      return content.size() == 12 && content == "LineA\nLineB\n";
    }, "File::getContent(string)");

    TestCase([]() {
      test_file.Create();
      test_file.InsertLine("LineA");
      test_file.InsertLine("LineB");
      std::vector<DTU::String> content;
      test_file.getContent(content, true);
      return content.size() == 2 && content[1] == "LineB";
    }, "File::getContent(vector)");

    TestCase([]() {
      test_file.Create();
      test_file.InsertLine("Line");
      return !test_file.isEmpty();
    }, "File::InsertLine");

    TestCase([]() {
      return test_file.Create() && test_file.Close() && !test_file.isOpen();
    }, "File::Close");

    TestCase([]() {
      return test_file.Open(true) && test_file.Exists();
    }, "File::Open(true)");

    TestCase([]() {
      return !test_file.Open() && !test_file.Exists();
    }, "File::Open(false)");

    TestCase([]() {
      return test_file.getLocation() == "File/File2/";
    }, "File::getLocation");

    TestCase([]() {
      return test_file.getName() == "test";
    }, "File::getName");

    TestCase([]() {
      return test_file.getExtension() == ".txt";
    }, "File::getExtension");

    TestCase([]() {
      return test_file.getFullPath() == "File/File2/test.txt";
    }, "File::getFullPath");

  }
}