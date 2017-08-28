#pragma once

#include <string>
#include <functional>

#include "ExamBoard.h"

namespace Core {
  /// <summary>
  /// Base class to be used when producing unit tests.
  /// Derived classes will be provided to Core::ExamBoard for examination.
  /// </summary>
  class UnitTest {
    friend class Core::ExamBoard;
  public:
            /// <summary>
            /// <i>Pure virtual function.</i><br/>
            /// Enacts the unique test cases for each derived test class.
            /// </summary>
    virtual void                  Examine       () = 0;

            /// <summary>
            /// Collects the name of the unit test.
            /// </summary>
            const std::string&    getName       () const;

            /// <summary>
            /// Checks whether the unit test performed all of its tests successfully.
            /// </summary>
            bool                  getPassed     () const;

            /// <summary>
            /// Gets the total number of tests performed.
            /// </summary>
            unsigned int          getTestCount  () const;

            /// <summary>
            /// <i>Virtual function.</i><br/>
            /// Gets the total number of tests passed.
            /// </summary>
            unsigned int          getPassCount  () const;
  protected:
                                  /// <summary>
                                  /// Constructor of the object.
                                  /// </summary>
                                  /// <param name = "name">The name of the unit test being performed.</param>
                                  UnitTest      (const std::string&);



            /// <summary>
            /// Performs the provided test function, updating the test results accordingly.
            /// </summary>
            /// <param name = "testMethod">The test method to be performed; returning <b>true</b> if successful.</param>
            /// <param name = "message">A label to identify the purpose of the test case.</param>
            void                  TestCase      (const std::function<bool()>&, const std::string& = "");

            /// <summary>
            /// Resets the test environment if necessary. Some objects may otherwise allow for data to carry over.
            /// </summary>
    virtual void                  Reset         () = 0;
  private:
    const std::string             m_name        { " _____ " };

    unsigned int                  m_testCount   { 0 };
    unsigned int                  m_passCount   { 0 };
  };
}

#define _UNIT_TEST_CLASS(OBJECT, CONSTRUCT, NAME)   \
  class OBJECT : public Core::UnitTest {            \
    friend class Core::ExamBoard;                   \
  public:                                           \
    void  Examine   () override final;              \
  protected:                                        \
          CONSTRUCT () : UnitTest(NAME) {}          \
    void  Reset     () override final;              \
  };

#define UNIT_TEST(OBJECT, NAME) _UNIT_TEST_CLASS(OBJECT, OBJECT, NAME)