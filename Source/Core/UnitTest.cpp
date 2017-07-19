#include "UnitTest.h"

#include "Log.h"

namespace Core {
  UnitTest::UnitTest(const std::string& name) : m_name(name) {}

  const std::string& UnitTest::getName() const {
    return m_name;
  }

  bool UnitTest::getPassed() const {
    return m_testCount == m_passCount;
  }

  unsigned int UnitTest::getTestCount() const {
    return m_testCount;
  }

  unsigned int UnitTest::getPassCount() const {
    return m_passCount;
  }

  void UnitTest::TestCase(const std::function<bool()>& testMethod) {
    ++m_testCount;
    try {
      if (testMethod())
        ++m_passCount;
    } catch (std::exception&) {}
  }
}