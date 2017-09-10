#include "ExamBoard.h"

#include "Log.h"
#include "File.h"
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

    LOG->PrintBreak();
    LOG->Print(String::Format(
      "////////////////////////////////////\n%s\n////////////////////////////////////\n%s\n%s\n////////////////////////////////////",
      messageNote.c_str(),
      String::Format(" Unit test results:     %i out of %i.", m_examPassCount, m_examCount).c_str(),
      String::Format(" Function test results: %i out of %i.", m_testPassCount, m_testCount).c_str()
    ), logType | Log::UNIT_TEST | Log::LOW);

    File::DestroyAll();
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
      logType | Log::UNIT_TEST | Log::MEDIUM);
  }
}