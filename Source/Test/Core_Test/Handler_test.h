#pragma once

#include <Core\UnitTest.h>

namespace Core_Test {

  class Handler : public Core::UnitTest {
    friend class Core::ExamBoard;
  public:
    void  Examine () override final;
  protected:
          Handler ();
    void  Reset   () override final;
  };

}