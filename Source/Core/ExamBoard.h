#pragma once

#include <string>
#include <iostream>
#include <assert.h>

#include "UnitTest.h"
#include "Singleton.h"

namespace Core {
  class ExamBoard : public Singleton<ExamBoard> {
    friend Singleton;
  public:
    template <typename T> void  Examine         ();
                          void  Results         ();
  protected:
                                ExamBoard       () = default;
                                ExamBoard       (const std::string&);
  private:
    const std::string           m_name          { " ____ " };

    unsigned int                m_examCount     { 0 };
    unsigned int                m_examPassCount { 0 };
    unsigned int                m_testCount     { 0 };
    unsigned int                m_testPassCount { 0 };
  };

  template <typename T>
  void ExamBoard::Examine() {
    UnitTest* unitTest = dynamic_cast<UnitTest*>(new T);

    assert(unitTest && !unitTest->getExamined());

    unitTest->Examine();

    if (unitTest->getPassed()) {
      ++m_examPassCount;
    }

    // TODO :: Debug outcome.

    ++m_examCount;
    m_testCount += unitTest->getTestCount();
    m_testPassCount += unitTest->getPassCount();

    delete unitTest;
  }
}