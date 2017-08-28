#include "declerations.h"

#include <Core\File.h>
#include <Core\StringUtil.h>

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
      return test_file.Create() && test_file.Close() && !test_file.isOpen();
    }, "File::Close");

    TestCase([]() {
      return test_file.Open(true) && test_file.Exists();
    }, "File::Open(true)");

    TestCase([]() {
      return !test_file.Open() && !test_file.Exists();
    }, "File::Open(false)");

    TestCase([]() {
      return Core::String::Compare(test_file.getLocation(), "File/File2/");
    }, "File::getLocation");

    TestCase([]() {
      return Core::String::Compare(test_file.getName(), "test");
    }, "File::getName");

    TestCase([]() {
      return Core::String::Compare(test_file.getExtension(), ".txt");
    }, "File::getExtension");

    TestCase([]() {
      return Core::String::Compare(test_file.getFullPath(), "File/File2/test.txt");
    }, "File::getFullPath");

  }
}