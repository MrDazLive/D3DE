#include "UnitTest.h"

namespace Core {
  UnitTest::UnitTest(const std::string& name) : m_name(name) {}

  void UnitTest::Examine() {
    if (!m_examined) {
      Perform();

      // TODO :: Debug outcome.

      m_examined = true;
    }
  }

  bool UnitTest::getPassed() const {
    return m_testCount == m_passCount;
  }

  bool UnitTest::getExamined() const {
    return m_examined;
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