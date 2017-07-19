#pragma once

#include <string>
#include <functional>
#include "Singleton.h"

namespace Core {
  class UnitTest {
  public:
    virtual void                  Examine       () {}

            const std::string&    getName       () const;

            bool                  getPassed     () const;
            unsigned int          getTestCount  () const;
            unsigned int          getPassCount  () const;
  protected:
                                  UnitTest      (const std::string&);

            void                  TestCase      (const std::function<bool()>&);
  private:
    const std::string             m_name        { " _____ " };

    unsigned int                  m_testCount   { 0 };
    unsigned int                  m_passCount   { 0 };
  };
}