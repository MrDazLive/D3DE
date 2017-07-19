#pragma once

#include <string>

#include "Singleton.h"

namespace Core {
  class UnitTest;

  class ExamBoard : public Singleton<ExamBoard> {
    friend Singleton;
  public:
    template <typename T> void  Examine         ();
                          void  Results         ();
  protected:
                                ExamBoard       () = default;
                                ExamBoard       (const std::string&);

                          void  Examine         (UnitTest* const);
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
    Examine(unitTest);
    delete unitTest;
  }
}