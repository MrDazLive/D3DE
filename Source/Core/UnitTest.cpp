#include "UnitTest.h"

#include "Log.h"

namespace Core {
  UnitTest::UnitTest(const DTU::String& name) : m_name(name) {}

  const DTU::String& UnitTest::getName() const {
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

  void UnitTest::TestCase(const std::function<bool()>& testMethod, const DTU::String& message) {
    ++m_testCount;
    Reset();
    try {
      if (testMethod()) {
        ++m_passCount;
        return;
      }
    } catch (std::exception&) {}
    LOG->PrintError(DTU::String("%s: Test %i failed. [%s]", m_name.c_str(), m_testCount, message.c_str()), Log::UNIT_TEST);
  }
}