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
            /// <param name = "testMethod"> The test method to be performed; returning <b>true</b> if successful.</param>
            void                  TestCase      (const std::function<bool()>&);
  private:
    const std::string             m_name        { " _____ " };

    unsigned int                  m_testCount   { 0 };
    unsigned int                  m_passCount   { 0 };
  };
}