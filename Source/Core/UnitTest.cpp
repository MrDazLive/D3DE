#include "UnitTest.h"

#include "Log.h"
#include "StringUtil.h"

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
    Reset();
    try {
      if (testMethod()) {
        ++m_passCount;
        return;
      }
    } catch (std::exception&) {}
    LOG->DebugError(String::Format("%s: Test %i failed.", m_name.c_str(), m_testCount));
  }
}