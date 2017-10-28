#pragma once

#include <string>

namespace DTU {

  struct String {
  private:
    std::string           m_data          { "" };
  public:
                          /// <summary>
                          /// Default constructor.
                          /// </summary>
                          String          () = default;

                          /// <summary>
                          /// Contructs a String with the value from the const char*.
                          /// </summary>
                          String          (const char*);

                          /// <summary>
                          /// Contructs a String with the value from the std::string.
                          /// </summary>
                          String          (const std::string&);

                          /// <summary>
                          /// Copy constructor produces a string with the same value as that provided.
                          /// </summary>
                          String          (const String&);

    /// <summary>
    /// Gets the contents of the string as a const char*.
    /// </summary>
    const char*           c_str           () const;

    /// <summary>
    /// Gets the contents of the string as an std::string.
    /// </summary>
    const std::string&    str             () const;

              operator    const char*     ();
              operator    std::string&    ();

    char&     operator    []              (const size_t);

    bool      operator    ==              (const char* o) const;
    bool      operator    ==              (const std::string&) const;
    bool      operator    ==              (const String&) const;

    bool      operator    !=              (const char* o) const;
    bool      operator    !=              (const std::string&) const;
    bool      operator    !=              (const String&) const;

    bool      operator    <               (const String&) const;
    bool      operator    >               (const String&) const;

    String    operator    +               (const String&) const;
    String&   operator    =               (const String&);
    String&   operator    +=              (const String&);

    /// <summary>
    /// Gets the number of charcters in the string.
    /// </summary>
    size_t                size            () const;

    /// <summary>
    /// Produces a copy of the string with all charcters in upper case.
    /// </summary>
    String                upper           () const;

    /// <summary>
    /// Produces a copy of the string with all charcters in lower case.
    /// </summary>
    String                lower           () const;

    /// <summary>
    /// Converts all characters to upper case.
    /// </summary>
    String&               toUpper         ();

    /// <summary>
    /// Converts all charcters to lower case.
    /// </summary>
    String&               toLower         ();

    /// <summary>
    /// Formats the value of the strin using provided arguments.
    /// </summary>
    /// <param name = "args">The arguments to be formatted into the string.</param>
    /// <returns>The formatted string.</returns>
    /// <b>Example</b><br/>
    /// <i>Code</i>
    /// <code>
    /// void main() {
    ///   DTU::String text("%i is an interger and %.3f is a float.");
    ///   text.format(3, 0.142f);
    ///   std::cout << text.c_str() << std::endl;
    /// }
    /// </code>
    /// <i>Output</i>
    /// <code>
    /// 3 is an interger and 0.142 is a float.
    /// </code>
    template <typename ... V>
    String&               format          (V...);


    /// <summary>
    /// Produces a formatted string object using the provided arguments.
    /// </summary>
    /// <param name = "text">The string to be formatted, followed by the arguments to be formatted in.</param>
    /// <returns>The formatted string.</returns>
    /// <b>Example</b><br/>
    /// <i>Code</i>
    /// <code>
    /// void main() {
    ///   DTU::String text = DTU::String::Format("%i is an interger and %.3f is a float.", 3, 0.142f);
    ///   std::cout << text.c_str() << std::endl;
    /// }
    /// </code>
    /// <i>Output</i>
    /// <code>
    /// 3 is an interger and 0.142 is a float.
    /// </code>
    static String         Format          (const String&...);

    /// <summary>
    /// Checks if the current string starts with one of the provided characters.
    /// </summary>
    /// <param name = "text">The string containing the characters the string can start with.</param>
    /// <b>Example</b><br/>
    /// <i>Code</i>
    /// <code>
    /// void main() {
    ///   DTU::String text("https://google.com");
    ///   std::cout << text.startsWith("efgh") << std::endl;
    /// }
    /// </code>
    /// <i>Output</i>
    /// <code>
    /// true
    /// </code>
    bool                  startsWith      (const String&) const;

    /// <summary>
    /// Checks if the current string starts with the provided phrase.
    /// </summary>
    /// <param name = "text">The phrase the text should start with.</param>
    /// <b>Example</b><br/>
    /// <i>Code</i>
    /// <code>
    /// void main() {
    ///   DTU::String text("https://google.com");
    ///   std::cout << text.startsWithText("https://") << std::endl;
    /// }
    /// </code>
    /// <i>Output</i>
    /// <code>
    /// true
    /// </code>
    bool                  startsWithText  (const String&) const;

    /// <summary>
    /// Checks if the current string ends with one of the provided characters.
    /// </summary>
    /// <param name = "text">The string containing the characters the string can end with.</param>
    /// <b>Example</b><br/>
    /// <i>Code</i>
    /// <code>
    /// void main() {
    ///   DTU::String text("https://google.com");
    ///   std::cout << text.endsWith("lmno") << std::endl;
    /// }
    /// </code>
    /// <i>Output</i>
    /// <code>
    /// true
    /// </code>
    bool                  endsWith        (const String&) const;

    /// <summary>
    /// Checks if the current string ends with the provided phrase.
    /// </summary>
    /// <param name = "text">The phrase the text should end with.</param>
    /// <b>Example</b><br/>
    /// <i>Code</i>
    /// <code>
    /// void main() {
    ///   DTU::String text("https://google.com");
    ///   std::cout << text.endsWithText(".com") << std::endl;
    /// }
    /// </code>
    /// <i>Output</i>
    /// <code>
    /// true
    /// </code>
    bool                  endsWithText    (const String&) const;
  };

  template <typename ... V>
  String& String::format(V... args) {
    *this = Format(*this, args...);
    return *this;
  }

}