#include "ExamBoard.h"

#include "Log.h"
#include "UnitTest.h"
#include "StringUtil.h"

#include <assert.h>

namespace Core {
  ExamBoard::ExamBoard(const std::string& name) : m_name(name) {}

  void ExamBoard::Examine(UnitTest* const unitTest) {
    assert(unitTest);

    unitTest->Examine();

    Logger->DebugError("TODO :: Log test results.");

    if (unitTest->getPassed()) {
      ++m_examPassCount;
    }

    ++m_examCount;
    m_testCount += unitTest->getTestCount();
    m_testPassCount += unitTest->getPassCount();
  }

  void ExamBoard::Results() {
    if (m_examCount == 0) {
      Logger->DebugMessage("////////////////////////////////////");
      Logger->DebugMessage("         No tests provided!         ");
      Logger->DebugMessage("////////////////////////////////////");
      Logger->DebugMessage(String::Format(" Unit test results:     %i out of %i.", m_examPassCount, m_examCount));
      Logger->DebugMessage(String::Format(" Function test results: %i out of %i.", m_testPassCount, m_testCount));
      Logger->DebugMessage("////////////////////////////////////");
    } else if (m_examCount == m_examPassCount) {
      Logger->DebugSuccess("////////////////////////////////////");
      Logger->DebugSuccess("     All tests were successful!     ");
      Logger->DebugSuccess("////////////////////////////////////");
      Logger->DebugSuccess(String::Format(" Unit test results:     %i out of %i.", m_examPassCount, m_examCount));
      Logger->DebugSuccess(String::Format(" Function test results: %i out of %i.", m_testPassCount, m_testCount));
      Logger->DebugSuccess("////////////////////////////////////");
    } else if (m_examPassCount > 0) {
      Logger->DebugWarning("////////////////////////////////////");
      Logger->DebugWarning("     Some tests were successful!    ");
      Logger->DebugWarning("////////////////////////////////////");
      Logger->DebugWarning(String::Format(" Unit test results:     %i out of %i.", m_examPassCount, m_examCount));
      Logger->DebugWarning(String::Format(" Function test results: %i out of %i.", m_testPassCount, m_testCount));
      Logger->DebugWarning("////////////////////////////////////");
    } else {
      Logger->DebugError("////////////////////////////////////");
      Logger->DebugError("       All tests were failed!       ");
      Logger->DebugError("////////////////////////////////////");
      Logger->DebugError(String::Format(" Unit test results:     %i out of %i.", m_examPassCount, m_examCount));
      Logger->DebugError(String::Format(" Function test results: %i out of %i.", m_testPassCount, m_testCount));
      Logger->DebugError("////////////////////////////////////");
    }
  }
}