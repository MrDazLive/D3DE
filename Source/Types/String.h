#pragma once

#include <string>

namespace DTU {

  class String {
  public:
                          String      () = default;
                          String      (const char*);
                          String      (const std::string&);
                          String      (const String&);

    const char*           c_str       () const;
    const std::string&    str         () const;

              operator    const char*  ();
              operator    std::string& ();

    char&     operator    []            (const size_t);

    bool      operator    ==            (const char* o);
    bool      operator    ==            (const std::string&);
    bool      operator    ==            (const String&);

    bool      operator    !=            (const char* o);
    bool      operator    !=            (const std::string&);
    bool      operator    !=            (const String&);

    String    operator    +             (const String&);
    String&   operator    =             (const String&);
    String&   operator    +=            (const String&);

    size_t                size          () const;
  private:
    std::string m_data { "" };
  };

}