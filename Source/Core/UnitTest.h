#pragma once

#include <string>
#include <functional>
#include "Singleton.h"

namespace Core {
  class UnitTest {
  public:
            void            Examine       ();

            bool            getPassed     () const;
            bool            getExamined   () const;
            unsigned int    getTestCount  () const;
            unsigned int    getPassCount  () const;
  protected:
                            UnitTest      (const std::string&);
            void            TestCase      (const std::function<bool()>&);
    virtual void            Perform       () {};
  private:
    const std::string       m_name        { " _____ " };
    bool                    m_examined    { false };
    unsigned int            m_testCount   { 0 };
    unsigned int            m_passCount   { 0 };
  };
}