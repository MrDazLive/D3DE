#pragma once

#include <string>

namespace DTU {

  class String {
  public:
                          String          () = default;
                          String          (const char*);
                          String          (const std::string&);
                          String          (const String&);

    const char*           c_str           () const;
    const std::string&    str             () const;

              operator    const char*     ();
              operator    std::string&    ();

    char&     operator    []              (const size_t);

    bool      operator    ==              (const char* o);
    bool      operator    ==              (const std::string&);
    bool      operator    ==              (const String&);

    bool      operator    !=              (const char* o);
    bool      operator    !=              (const std::string&);
    bool      operator    !=              (const String&);

    String    operator    +               (const String&);
    String&   operator    =               (const String&);
    String&   operator    +=              (const String&);

    size_t                size            () const;

    String                upper           () const;
    String                lower           () const;
    String&               toUpper         ();
    String&               toLower         ();

    template <typename ... V>
    String&               format          (V...);
    static String         Format          (const String&...);

    bool                  startsWith      (const String&) const;
    bool                  startsWithText  (const String&) const;

    bool                  endsWith        (const String&) const;
    bool                  endsWithText    (const String&) const;
  private:
    std::string m_data { "" };
  };

  template <typename ... V>
  String& String::format(V... args) {
    *this = Format(*this, args...);
    return *this;
  }

}