#pragma once

#include "Vector3.h"

namespace DTU {

  template <typename T>
  struct Vector4 {
    T                   x                 { 0 };
    T                   y                 { 0 };
    T                   z                 { 0 };
    T                   w                 { 0 };
    
                        /// <summary>
                        /// Default constructor.
                        /// </summary>
                        Vector4           () = default;

                        /// <summary>
                        /// Contructs a Vector4, setting each elements with the provided value.
                        /// </summary>
                        Vector4           (const T&);

                        /// <summary>
                        /// Contructs a Vector4, setting each element respectively with the provided values.
                        /// </summary>
                        Vector4           (const T&, const T&, const T&, const T&);

                        /// <summary>
                        /// Contructs a Vector4, setting each element respective from the Vector2.
                        /// </summary>
                        Vector4           (const Vector2<T>&);

                        /// <summary>
                        /// Contructs a Vector4, setting each element respective from the Vector3.
                        /// </summary>
                        Vector4           (const Vector3<T>&);

                        /// <summary>
                        /// Copy constructor produces a Vector4, setting each element with the same value as that provided.
                        /// </summary>
                        Vector4           (const Vector4<T>&);

                        /// <summary>
                        /// Constructs a Vector4, setting each element repsectively with the first two elements of the provided array.
                        /// </summary>
                        Vector4           (const T*);

              operator  const T*          ();

    T&        operator  []                (const size_t);

    bool      operator  ==                (const Vector4<T>&) const;
    bool      operator  !=                (const Vector4<T>&) const;

    bool      operator  <                 (const Vector4<T>&) const;
    bool      operator  >                 (const Vector4<T>&) const;

    Vector4   operator  +                 (const Vector4<T>&) const;
    Vector4   operator  -                 (const Vector4<T>&) const;
    Vector4   operator  *                 (const T&) const;
    Vector4   operator  /                 (const T&) const;
    Vector4   operator  *                 (const Vector4<T>&) const;
    Vector4   operator  /                 (const Vector4<T>&) const;
    Vector4&  operator  =                 (const Vector4<T>&);

    Vector4&  operator  +=                (const Vector4<T>&);
    Vector4&  operator  -=                (const Vector4<T>&);
    Vector4&  operator  *=                (const T&);
    Vector4&  operator  /=                (const T&);
    Vector4&  operator  *=                (const Vector4<T>&);
    Vector4&  operator  /=                (const Vector4<T>&);

    /// <summary>
    /// Produces a copy of the Vector4 in a normalised state.
    /// </summary>
    Vector4             normalised        () const;
    
    /// <summary>
    /// Converts the Vector4 to a normalised state.
    /// </summary>
    Vector4&            normalise         ();

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
    T                   dot               (const Vector4<T>&) const;

    /// <summary>
    /// Calculates the dot product between the provided vectors.
    /// </summary>
    /// <params name = "l">The left hand vector to be used as part of the dot product.</params>
    /// <params name = "r">The right hand vector to be used as part of the dot product.</params>
    static T            dot               (const Vector4<T>&, const Vector4<T>&);
  };

  MATH_TYPES(Vector4)

  template <typename T>
  Vector4<T>::Vector4(const T& val) {
    x = val;
    y = val;
    z = val;
    w = val;
  }

  template <typename T>
  Vector4<T>::Vector4(const T& x, const T& y, const T& z, const T& w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }

  template <typename T>
  Vector4<T>::Vector4(const Vector2<T>& val) {
    this->x = val.x;
    this->y = val.y;
  }

  template <typename T>
  Vector4<T>::Vector4(const Vector3<T>& val) {
    this->x = val.x;
    this->y = val.y;
    this->z = val.z;
  }

  template <typename T>
  Vector4<T>::Vector4(const Vector4<T>& val) {
    *this = val;
  }

  template <typename T>
  Vector4<T>::Vector4(const T* val) {
    x = val[0];
    y = val[1];
    z = val[2];
    w = val[3];
  }

  template <typename T>
  Vector4<T>::operator const T* () {
    return &x;
  }

  template <typename T>
  T& Vector4<T>::operator[](const size_t idx) {
    switch(idx) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      case 3:
        return w;
      default:
        throw std::out_of_range("Index out of bounds");
    }
  }

  template <>
  bool Vector4<float>::operator == (const Vector4<float>& o) const;

  template <>
  bool Vector4<double>::operator == (const Vector4<double>& o) const;

  template <typename T>
  bool Vector4<T>::operator == (const Vector4<T>& o) const {
    return x == o.x && y == o.y && z == o.z && w == o.w;
  }

  template <typename T>
  bool Vector4<T>::operator != (const Vector4<T>& o) const {
    return x != o.x || y != o.y || z != o.z || w != o.w;
  }

  template <typename T>
  bool Vector4<T>::operator < (const Vector4<T>& o) const {
    return magnitudeSquared() < o.magnitudeSquared();
  }

  template <typename T>
  bool Vector4<T>::operator > (const Vector4<T>& o) const {
    return magnitudeSquared() > o.magnitudeSquared();
  }

  template <typename T>
  Vector4<T> Vector4<T>::operator + (const Vector4<T>& o) const {
    return Vector4(x + o.x, y + o.y, z + o.z, w + o.w);
  }

  template <typename T>
  Vector4<T> Vector4<T>::operator - (const Vector4<T>& o) const {
    return Vector4(x - o.x, y - o.y, z - o.z, w - o.w);
  }

  template <typename T>
  Vector4<T> Vector4<T>::operator * (const T& v) const {
    return Vector4(x * v, y * v, z * v, w * v);
  }

  template <typename T>
  Vector4<T> Vector4<T>::operator / (const T& v) const {
    if(v == 0)
      throw std::overflow_error("Divide by zero exception");
    return Vector4(x / v, y / v, z / v, w / v);
  }

  template <typename T>
  Vector4<T> Vector4<T>::operator * (const Vector4<T>& o) const {
    return Vector4(x * o.x, y * o.y, z * o.z, w * o.w);
  }

  template <typename T>
  Vector4<T> Vector4<T>::operator / (const Vector4<T>& o) const {
    if(o.x == 0 || o.y == 0 || o.z == 0 || o.w == 0)
      throw std::overflow_error("Divide by zero exception");
    return Vector4(x / o.x, y / o.y, z / o.z, w / o.w);
  }

  template <typename T>
  Vector4<T>& Vector4<T>::operator = (const Vector4<T>& o) {
    x = o.x;
    y = o.y;
    z = o.z;
    w = o.w;
    return *this;
  }

  template <typename T>
  Vector4<T>& Vector4<T>::operator += (const Vector4<T>& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    w += o.w;
    return *this;
  }

  template <typename T>
  Vector4<T>& Vector4<T>::operator -= (const Vector4<T>& o) {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    w -= o.w;
    return *this;
  }

  template <typename T>
  Vector4<T>& Vector4<T>::operator *= (const T& v) {
    x *= v;
    y *= v;
    z *= v;
    w *= w;
    return *this;
  }

  template <typename T>
  Vector4<T>& Vector4<T>::operator /= (const T& v) {
    if(v == 0)
      throw std::overflow_error("Divide by zero exception");
    x /= v;
    y /= v;
    z /= v;
    w /= v;
    return *this;
  }

  template <typename T>
  Vector4<T>& Vector4<T>::operator *= (const Vector4<T>& o) {
    x *= o.x;
    y *= o.y;
    z *= o.z;
    w *= o.w;
    return *this;
  }

  template <typename T>
  Vector4<T>& Vector4<T>::operator /= (const Vector4<T>& o) {
    if(o.x == 0 || o.y == 0)
      throw std::overflow_error("Divide by zero exception");
    x /= o.x;
    y /= o.y;
    z /= o.z;
    w /= o.w;
    return *this;
  }

  template <typename T>
  Vector4<T> Vector4<T>::normalised() const {
    return *this / magnitude();
  }

  template <>
  Vector4<int>& Vector4<int>::normalise();

  template <>
  Vector4<unsigned int>& Vector4<unsigned int>::normalise();

  template <typename T>
  Vector4<T>& Vector4<T>::normalise() {
    *this /= magnitude();
    return *this;
  }

  template <typename T>
  double Vector4<T>::magnitude() const {
    return sqrt(magnitudeSquared());
  }

  template <typename T>
  double Vector4<T>::magnitudeSquared() const {
    return (double)((x * x) + (y * y) + (z * z) + (w * w));
  }

  template <typename T>
  T Vector4<T>::dot(const Vector4<T>& o) const {
    return (x * o.x) + (y * o.y) + (z * o.z) + (w * o.w);
  }

  template <typename T>
  T Vector4<T>::dot(const Vector4<T>& l, const Vector4<T>& r) {
    return l.dot(r);
  }

}