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
    std::string Format(const char* text, V... args) {
      char buffer[1024];
      sprintf_s(buffer, text, args...);
      return std::string(buffer);
    }

  }
}