#include "String.h"

#include <cstdarg>
#include <algorithm>

namespace DTU {

  String::String(const char* val) {
    m_data = std::string(val);
  }

  String::String(const std::string& val) {
    m_data = val;
  }

  String::String(const String& val) {
    m_data = val.str();
  }
  
  String::operator const char*() {
    return m_data.c_str();
  }

  String::operator std::string&() {
    return m_data;
  }

  const char* String::c_str() const {
    return m_data.c_str();
  }

  const std::string& String::str() const {
    return m_data;
  }

  char& String::operator[](const size_t idx) {
    return m_data[idx];
  }

  bool String::operator==(const char* o) const {
    return m_data.compare(o) == 0;
  }

  bool String::operator==(const std::string& o) const {
    return size() == o.size()
      && m_data.compare(o) == 0;
  }

  bool String::operator==(const String& o) const {
    return size() == o.size()
      && m_data.compare(o.str()) == 0;
  }

  bool String::operator!=(const char* o) const {
    return m_data.compare(o) != 0;
  }

  bool String::operator!=(const std::string& o) const {
    return size() != o.size()
      || m_data.compare(o) != 0;
  }

  bool String::operator!=(const String& o) const {
    return size() != o.size()
      || m_data.compare(o.str()) != 0;
  }

  bool String::operator<(const String& o) const {
    return m_data < o.m_data;
  }

  bool String::operator>(const String& o) const {
    return m_data > o.m_data;
  }

  String String::operator+(const String& o) const {
    return String(m_data + o.str());
  }

  String& String::operator=(const String& o) {
    m_data = o.str();
    return *this;
  }

  String& String::operator+=(const String& o) {
    m_data += o.str();
    return *this;
  }

  size_t String::size() const {
    return m_data.size();
  }

  String String::upper() const {
    String s(*this);
    return s.toUpper();
  }

  String String::lower() const {
    String s(*this);
    return s.toLower();
  }

  String& String::toUpper() {
    std::transform(m_data.begin(), m_data.end(), m_data.begin(),
      [](unsigned char c){ return std::toupper(c); });
    return *this;
  }

  String& String::toLower() {
    std::transform(m_data.begin(), m_data.end(), m_data.begin(),
      [](unsigned char c){ return std::tolower(c); });
    return *this;
  }

  String String::Format(const String& text...) {
    char b[1024];
    va_list list;
    va_start(list, text);
    vsprintf(b, text.c_str(), list);
    va_end(list);
    return String(b);
  }

  bool String::startsWith(const String& text) const {
    const size_t c = m_data.find_first_of(text.str());
    return c == 0;
  }

  bool String::startsWithText(const String& text) const {
    return m_data.find(text.str()) == 0;
  }

  bool String::endsWith(const String& text) const {
    const size_t c = m_data.find_last_of(text.str());
    return c == size() - 1;
  }

  bool String::endsWithText(const String& text) const {
    return m_data.rfind(text.str()) == size() - text.size();
  }
}