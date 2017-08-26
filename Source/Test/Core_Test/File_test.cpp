#include "declerations.h"

#include <Core\File.h>

Core::File test_file("test.txt");

namespace Core_Test {
  void File::Reset() {
    test_file.Delete();
  }

  void File::Examine() {
    TestCase([]() {
      return !test_file.Exists();
    });

    TestCase([]() {
      return test_file.Create() && test_file.Exists();
    });

    TestCase([]() {
      return test_file.Create() && test_file.Delete() && !test_file.Exists();
    });

    TestCase([]() {
      return test_file.Create() && test_file.Create(true) && test_file.Exists();
    });

  }
}