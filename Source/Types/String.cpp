#include "String.h"

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

  bool String::operator==(const char* o) {
    return m_data.compare(o) == 0;
  }

  bool String::operator==(const std::string& o) {
    return size() == o.size()
      && m_data.compare(o) == 0;
  }

  bool String::operator==(const String& o) {
    return size() == o.size()
      && m_data.compare(o.str()) == 0;
  }

  bool String::operator!=(const char* o) {
    return m_data.compare(o) != 0;
  }

  bool String::operator!=(const std::string& o) {
    return size() != o.size()
      || m_data.compare(o) == 0;
  }

  bool String::operator!=(const String& o) {
    return size() != o.size()
      || m_data.compare(o.str()) == 0;
  }

  String String::operator+(const String& o) {
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

}