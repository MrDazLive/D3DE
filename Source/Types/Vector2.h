#pragma once

#include "defines.h"
#include <cmath>

namespace DTU {

  template <typename T>
  struct Vector2 {
    T                   x                 { 0 };
    T                   y                 { 0 };

    static Vector2<T>   zero, up, down, left, right;
    
                        /// <summary>
                        /// Default constructor.
                        /// </summary>
                        Vector2           () = default;

                        /// <summary>
                        /// Contructs a Vector2, setting each elements with the provided value.
                        /// </summary>
                        Vector2           (const T&);

                        /// <summary>
                        /// Contructs a Vector2, setting each element respectively with the provided values.
                        /// </summary>
                        Vector2           (const T&, const T&);

                        /// <summary>
                        /// Copy constructor produces a Vector2, setting each element with the same value as that provided.
                        /// </summary>
                        Vector2           (const Vector2<T>&);

                        /// <summary>
                        /// Constructs a Vectors, setting seach element repsectively with the first two elements of the provided array.
                        /// </summary>
                        Vector2           (const T*);

              operator  const T*          ();

    T&        operator  []                (const size_t);

    bool      operator  ==                (const Vector2<T>&) const;
    bool      operator  !=                (const Vector2<T>&) const;

    bool      operator  <                 (const Vector2<T>&) const;
    bool      operator  >                 (const Vector2<T>&) const;

    Vector2   operator  +                 (const Vector2<T>&) const;
    Vector2   operator  -                 (const Vector2<T>&) const;
    Vector2   operator  *                 (const T&) const;
    Vector2   operator  /                 (const T&) const;
    Vector2   operator  *                 (const Vector2<T>&) const;
    Vector2   operator  /                 (const Vector2<T>&) const;
    Vector2&  operator  =                 (const Vector2<T>&);

    Vector2&  operator  +=                (const Vector2<T>&);
    Vector2&  operator  -=                (const Vector2<T>&);
    Vector2&  operator  *=                (const T&);
    Vector2&  operator  /=                (const T&);
    Vector2&  operator  *=                (const Vector2<T>&);
    Vector2&  operator  /=                (const Vector2<T>&);

    /// <summary>
    /// Produces a copy of the Vector2 in a normalised state.
    /// </summary>
    Vector2             normalised        () const;
    
    /// <summary>
    /// Converts the Vector2 to a normalised state.
    /// </summary>
    Vector2&            normalise         ();

    /// <summary>
    /// Calculates the magnitude(length) of the vector.
    /// </summary>
    double              magnitude         () const;

    /// <summary>
    /// Calculates the squared magnitude(length) of the vector.
    /// </summary>
    double              magnitudeSquared  () const;

    /// <summary>
    /// Calculates the dot product againts the provided vector.
    /// </summary>
    /// <params name = "o">The other vector to be used as part of the dot product.</params>
    T                   dot               (const Vector2<T>&) const;

    /// <summary>
    /// Calculates the dot product between the provided vectors.
    /// </summary>
    /// <params name = "l">The left hand vector to be used as part of the dot product.</params>
    /// <params name = "r">The right hand vector to be used as part of the dot product.</params>
    static T            dot               (const Vector2<T>&, const Vector2<T>&);

    /// <summary>
    /// Calculates the angle against the provided vector.
    /// </summary>
    /// <params name = "o">The other vector to get the angle from.</params>
    double              angle             (const Vector2<T>&) const;

    /// <summary>
    /// Calculates the angle between the provided vectors.
    /// </summary>
    /// <params name = "l">The left hand vector to get the angle from.</params>
    /// <params name = "r">The right hand vector to get the angle from.</params>
    static double       angle             (const Vector2<T>&, const Vector2<T>&);
  };

  MATH_TYPES(Vector2)

  template <typename T>
  Vector2<T> Vector2<T>::zero = Vector2<T>(0, 0);

  template <typename T>
  Vector2<T> Vector2<T>::up = Vector2<T>(0, 1);

  template <typename T>
  Vector2<T> Vector2<T>::down = Vector2<T>(0, -1);

  template <typename T>
  Vector2<T> Vector2<T>::left = Vector2<T>(-1, 0);

  template <typename T>
  Vector2<T> Vector2<T>::right = Vector2<T>(1, 0);

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

  template <typename T>
  Vector2<T> Vector2<T>::normalised() const {
    return *this / magnitude();
  }

  template <>
  Vector2<int>& Vector2<int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }

  template <>
  Vector2<unsigned int>& Vector2<unsigned int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }

  template <typename T>
  Vector2<T>& Vector2<T>::normalise() {
    *this /= magnitude();
    return *this;
  }

  template <typename T>
  double Vector2<T>::magnitude() const {
    return sqrt(magnitudeSquared());
  }

  template <typename T>
  double Vector2<T>::magnitudeSquared() const {
    return (double)((x * x) + (y * y));
  }

  template <typename T>
  T Vector2<T>::dot(const Vector2<T>& o) const {
    return (x * o.x) + (y * o.y);
  }

  template <typename T>
  T Vector2<T>::dot(const Vector2<T>& l, const Vector2<T>& r) {
    return l.dot(r);
  }

  template <typename T>
  double Vector2<T>::angle(const Vector2<T>& o) const {
    return acos(dot(o) / (magnitude() * o.magnitude()));
  }

  template <typename T>
  double Vector2<T>::angle(const Vector2<T>& l, const Vector2<T>& r) {
    return l.angle(r);
  }

}