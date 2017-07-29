#include "ExamBoard.h"

#include "Log.h"
#include "UnitTest.h"
#include "StringUtil.h"

namespace Core {
  ExamBoard::ExamBoard(const std::string& name) : m_name(name) {}

  void ExamBoard::Examine(UnitTest* const unitTest) {
    LOG->DebugAssert(unitTest != nullptr, "Provided object is not a valid UnitTest.");

    unitTest->Examine();

    PrintOutcome(unitTest);

    if (unitTest->getPassed()) {
      ++m_examPassCount;
    }
    ++m_examCount;

    m_testCount += unitTest->getTestCount();
    m_testPassCount += unitTest->getPassCount();
  }

  void ExamBoard::Results() {
    Log::Type logType = Log::MESSAGE;
    std::string messageNote = "";

    if (m_examCount == 0) {
      messageNote = "         No tests provided!         ";
    } else if (m_examCount == m_examPassCount) {
      logType = Log::SUCCESS;
      messageNote = "     All tests were successful!     ";
    } else if (m_examPassCount > 0) {
      logType = Log::WARNING;
      messageNote = "     Some tests were successful!    ";
    } else {
      logType = Log::ERROR;
      messageNote = "       All tests were failed!       ";
    }

    LOG->DebugBreak();
    LOG->Debug("////////////////////////////////////", logType);
    LOG->Debug(messageNote, logType);
    LOG->Debug("////////////////////////////////////", logType);
    LOG->Debug(String::Format(" Unit test results:     %i out of %i.", m_examPassCount, m_examCount), logType);
    LOG->Debug(String::Format(" Function test results: %i out of %i.", m_testPassCount, m_testCount), logType);
    LOG->Debug("////////////////////////////////////", logType);
  }

  void ExamBoard::PrintOutcome(UnitTest* const unitTest) {
    Log::Type logType = Log::WARNING;
    if (unitTest->getPassed()) {
      logType = Log::SUCCESS;
    } else if (unitTest->getPassCount() == 0) {
      logType = Log::ERROR;
    }

    LOG->Debug(
      String::Format("%s: %i out of %i passed.",
        unitTest->getName().c_str(),
        unitTest->getPassCount(),
        unitTest->getTestCount()),
      logType);
  }
}