#pragma once

#include <string>

#include "Singleton.h"

namespace Core {
  class UnitTest;

  /// <summary>
  /// Class used for performing and tracking the results of @link Core::UnitTest Core::UnitTests@endlink.
  /// </summary>
  class ExamBoard : public Singleton<ExamBoard> {
    friend Singleton;
  public:
    /// <summary>
    /// Enacts and prints the results of the provided Core::UnitTest.
    /// Template argument expects a type of Core::UnitTest.
    /// </summary>
    template <typename T>
    void                Examine         ();

    /// <summary>
    /// Evaluates and prints the results of the performed @link Core::UnitTest Core::UnitTests@endlink.
    /// </summary>
    bool                Results         ();
  protected:
                        /// <summary>
                        /// The default constructor of Core::ExamBoard. Providing no name identifier.
                        /// </summary>
                        ExamBoard       () = default;

                        /// <summary>
                        /// The expected constructor of Core::ExamBoard. Providing a name identifier.
                        /// </summary>
                        /// <param name = "name">The name used to identify the examination being undertaken.</param>
                        ExamBoard       (const std::string&);

    /// <summary>
    /// Enacts and prints the results of the provided Core::UnitTest.
    /// </summary>
    /// <param name = "unitTest">The Core::UnitTest to examine.</param>
    void                Examine         (UnitTest* const);
  private:
    /// <summary>
    /// Prints the outcome of the provided Core::UnitTest.
    /// </summary>
    /// <param name = "unitTest">The Core::UnitTest to print the results of."</param>
    void                PrintOutcome    (UnitTest* const);

    const std::string   m_name          { " ____ " };

    unsigned int        m_examCount     { 0 };
    unsigned int        m_examPassCount { 0 };
    unsigned int        m_testCount     { 0 };
    unsigned int        m_testPassCount { 0 };
  };

  template <typename T>
  void ExamBoard::Examine() {
    UnitTest* unitTest = dynamic_cast<UnitTest*>(new T);
    Examine(unitTest);
    delete unitTest;
  }
}