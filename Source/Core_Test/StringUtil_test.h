#pragma once

#include <Core\UnitTest.h>
#include <Core\ExamBoard.h>

namespace Core_Test {

  class String : public Core::UnitTest {
    friend class Core::ExamBoard;
  public:
    void  Examine () override final;
  protected:
          String  ();
  };

}