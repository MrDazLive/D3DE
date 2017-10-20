#pragma once

#include "defines.h"

namespace DTU {

  template <typename T>
  struct Vector2 {
    T x { 0 };
    T y { 0 };

    Vector2() = default;
    Vector2(const T&);
    Vector2(const T&, const T&);
    Vector2(const Vector2<T>&);
    Vector2(const T*);

    operator const T* ();

    T& operator[](const size_t);

    bool operator == (const Vector2<T>&) const;
    bool operator != (const Vector2<T>&) const;

    bool operator < (const Vector2<T>&) const;
    bool operator > (const Vector2<T>&) const;

    Vector2 operator + (const Vector2<T>&) const;
    Vector2 operator - (const Vector2<T>&) const;
    Vector2 operator * (const T&) const;
    Vector2 operator / (const T&) const;
    Vector2 operator * (const Vector2<T>&) const;
    Vector2 operator / (const Vector2<T>&) const;
    Vector2& operator = (const Vector2<T>&);

    Vector2& operator += (const Vector2<T>&);
    Vector2& operator -= (const Vector2<T>&);
    Vector2& operator *= (const T&);
    Vector2& operator /= (const T&);
    Vector2& operator *= (const Vector2<T>&);
    Vector2& operator /= (const Vector2<T>&);
  };

  MATH_TYPES(Vector2)

  template <typename T>
  Vector2<T>::Vector2(const T& val) {
    x = val;
    y = val;
  }

  template <typename T>
  Vector2<T>::Vector2(const T& x, const T& y) {
    this->x = x;
    this->y = y;
  }

  template <typename T>
  Vector2<T>::Vector2(const Vector2<T>& val) {
    *this = val;
  }

  template <typename T>
  Vector2<T>::Vector2(const T* val) {
    x = val[0];
    y = val[1];
  }

  template <typename T>
  Vector2<T>::operator const T* () {
    return &x;
  }

  template <typename T>
  T& Vector2<T>::operator[](const size_t idx) {
    switch(idx) {
      case 0:
        return x;
      case 1:
        return y;
      default:
        throw std::out_of_range("Index out of bounds");
    }
  }

  template <>
  bool Vector2<float>::operator == (const Vector2<float>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y);
  }

  template <>
  bool Vector2<double>::operator == (const Vector2<double>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y);
  }

  template <typename T>
  bool Vector2<T>::operator == (const Vector2<T>& o) const {
    return x == o.x && y == o.y;
  }

  template <typename T>
  bool Vector2<T>::operator != (const Vector2<T>& o) const {
    return x != o.x || y != o.y;
  }

  template <typename T>
  bool Vector2<T>::operator < (const Vector2<T>&) const {
    throw std::domain_error("");
    return false;
  }

  template <typename T>
  bool Vector2<T>::operator > (const Vector2<T>&) const {
    throw std::domain_error("");
    return false;
  }

  template <typename T>
  Vector2<T> Vector2<T>::operator + (const Vector2<T>& o) const {
    return Vector2(x + o.x, y + o.y);
  }

  template <typename T>
  Vector2<T> Vector2<T>::operator - (const Vector2<T>& o) const {
    return Vector2(x - o.x, y - o.y);
  }

  template <typename T>
  Vector2<T> Vector2<T>::operator * (const T& v) const {
    return Vector2(x * v, y * v);
  }

  template <typename T>
  Vector2<T> Vector2<T>::operator / (const T& v) const {
    if(v == 0)
      throw std::overflow_error("Divide by zero exception");
    return Vector2(x / v, y / v);
  }

  template <typename T>
  Vector2<T> Vector2<T>::operator * (const Vector2<T>& o) const {
    return Vector2(x * o.x, y * o.y);
  }

  template <typename T>
  Vector2<T> Vector2<T>::operator / (const Vector2<T>& o) const {
    if(o.x == 0 || o.y == 0)
      throw std::overflow_error("Divide by zero exception");
    return Vector2(x / o.x, y / o.y);
  }

  template <typename T>
  Vector2<T>& Vector2<T>::operator = (const Vector2<T>& o) {
    x = o.x;
    y = o.y;
    return *this;
  }

  template <typename T>
  Vector2<T>& Vector2<T>::operator += (const Vector2<T>& o) {
    x += o.x;
    y += o.y;
    return *this;
  }

  template <typename T>
  Vector2<T>& Vector2<T>::operator -= (const Vector2<T>& o) {
    x -= o.x;
    y -= o.y;
    return *this;
  }

  template <typename T>
  Vector2<T>& Vector2<T>::operator *= (const T& v) {
    x *= v;
    y *= v;
    return *this;
  }

  template <typename T>
  Vector2<T>& Vector2<T>::operator /= (const T& v) {
    if(v == 0)
      throw std::overflow_error("Divide by zero exception");
    x /= v;
    y /= v;
    return *this;
  }

  template <typename T>
  Vector2<T>& Vector2<T>::operator *= (const Vector2<T>& o) {
    x *= o.x;
    y *= o.y;
    return *this;
  }

  template <typename T>
  Vector2<T>& Vector2<T>::operator /= (const Vector2<T>& o) {
    if(o.x == 0 || o.y == 0)
      throw std::overflow_error("Divide by zero exception");
    x /= o.x;
    y /= o.y;
    return *this;
  }

}