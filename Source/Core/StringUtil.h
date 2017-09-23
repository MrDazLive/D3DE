#pragma once

#include <string>

namespace Core {
  namespace String {

    /// <summary>
    /// Produces a formatted string object using provided arguments.
    /// </summary>
    /// <param name = "text">The string to be formatted.</param>
    /// <param name = "args">The variadic arguments to be formatted into the string.</param>
    /// <returns>The formatted string.</returns>
    /// <b>Example</b><br/>
    /// <i>Code</i>
    /// <code>
    /// void main() {
    ///   std::string text = String::Format("%i is an interger and %.3f is a float.", 3, 0.142f);
    ///   std::cout << text << std::endl;
    /// }
    /// </code>
    /// <i>Output</i>
    /// <code>
    /// 3 is an interger and 0.142 is a float.
    /// </code>
    template <typename ... V>
    inline std::string Format(const char* text, V... args) {
      char buffer[1024];
      snprintf(buffer, 1023, text, args...);
      return std::string(buffer);
    }

    /// <summary>
    /// Compares the value of two provided strings (case sensitive).
    /// </summary>
    /// <returns>Whether the strings are identical or not.</returns>
    inline bool Equals(const std::string& l, const std::string& r) {
      return l.compare(r) == 0;
    }

    /// <summary>
    /// Checks that the string ends with one of the provided characters.
    /// </summary>
    /// <param name = "text">The string to be checked.</param>
    /// <param name = "args">The characters that the string can end with.</param>
    inline bool EndsWith(const std::string& text, const char* args) {
      const size_t last = text.find_last_of(args);
      return last != std::string::npos && last == text.length() - 1;
    }

  }
}