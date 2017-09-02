#include "ExamBoard.h"

#include "Log.h"
#include "UnitTest.h"
#include "StringUtil.h"

namespace Core {
  ExamBoard::ExamBoard(const std::string& name) : m_name(name) {}

  void ExamBoard::Examine(UnitTest* const unitTest) {
    LOG->PrintAssert(unitTest != nullptr, "Provided object is not a valid UnitTest.");

    unitTest->Examine();
    unitTest->Reset();

    PrintOutcome(unitTest);

    if (unitTest->getPassed()) {
      ++m_examPassCount;
    }
    ++m_examCount;

    m_testCount += unitTest->getTestCount();
    m_testPassCount += unitTest->getPassCount();
  }

  void ExamBoard::Results() {
    Log::Flag_ logType = Log::MESSAGE;
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

    logType |= Log::UNIT_TEST;

    LOG->PrintBreak();
    LOG->Print("////////////////////////////////////", logType);
    LOG->Print(messageNote, logType);
    LOG->Print("////////////////////////////////////", logType);
    LOG->Print(String::Format(" Unit test results:     %i out of %i.", m_examPassCount, m_examCount), logType);
    LOG->Print(String::Format(" Function test results: %i out of %i.", m_testPassCount, m_testCount), logType);
    LOG->Print("////////////////////////////////////", logType);

    system("pause");
  }

  void ExamBoard::PrintOutcome(UnitTest* const unitTest) {
    Log::Flag_ logType = Log::WARNING;
    if (unitTest->getPassed()) {
      logType = Log::SUCCESS;
    } else if (unitTest->getPassCount() == 0) {
      logType = Log::ERROR;
    }

    LOG->Print(
      String::Format("%s: %i out of %i passed.",
        unitTest->getName().c_str(),
        unitTest->getPassCount(),
        unitTest->getTestCount()),
      logType | Log::UNIT_TEST);
  }
}