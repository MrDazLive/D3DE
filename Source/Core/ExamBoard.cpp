#include "ExamBoard.h"

#include "Log.h"
#include "File.h"
#include "UnitTest.h"

namespace Core {
  const char* partition = "/////////////////////////////////////////\n";

  ExamBoard::ExamBoard(const DTU::String& name) : m_name(name) {
    LOG->PrintMessage(DTU::String(
      "%s%s%s",
      partition,
      DTU::String(" Examboard:              %s\n", m_name.c_str()).c_str(),
      partition
    ), Log::UNIT_TEST | Log::LOW);
  }

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

  bool ExamBoard::Results() {
    Log::Flags logType = Log::MESSAGE;
    DTU::String messageNote = "";

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
    LOG->Print(DTU::String(
      "%s%s\n%s%s%s%s%s",
      partition,
      messageNote.c_str(),
      partition,
      DTU::String(" Examboard:              %s.\n", m_name.c_str()).c_str(),
      DTU::String(" Unit test results:      %i out of %i.\n", m_examPassCount, m_examCount).c_str(),
      DTU::String(" Function test results:  %i out of %i.\n", m_testPassCount, m_testCount).c_str(),
      partition
    ), logType | Log::UNIT_TEST | Log::LOW);

    File::DestroyAll();
    return logType == Log::SUCCESS;
  }

  void ExamBoard::PrintOutcome(UnitTest* const unitTest) {
    Log::Flags logType = Log::WARNING;
    if (unitTest->getPassed()) {
      logType = Log::SUCCESS;
    } else if (unitTest->getPassCount() == 0) {
      logType = Log::ERROR;
    }

    LOG->Print(
      DTU::String("%s: %i out of %i passed.",
        unitTest->getName().c_str(),
        unitTest->getPassCount(),
        unitTest->getTestCount()),
      logType | Log::UNIT_TEST | Log::MEDIUM);
  }
}