#pragma once

#include "Vector2.h"

namespace DTU {

  template <typename T>
  struct Vector3 {
    T                   x                 { 0 };
    T                   y                 { 0 };
    T                   z                 { 0 };

    static Vector3<T>   zero, up, down, left, right, forward, backward;
    
                        /// <summary>
                        /// Default constructor.
                        /// </summary>
                        Vector3           () = default;

                        /// <summary>
                        /// Contructs a Vector3, setting each elements with the provided value.
                        /// </summary>
                        Vector3           (const T&);

                        /// <summary>
                        /// Contructs a Vector3, setting each element respectively with the provided values.
                        /// </summary>
                        Vector3           (const T&, const T&, const T&);

                        /// <summary>
                        /// Contructs a Vector3, setting each element respective from the Vector2.
                        /// </summary>
                        Vector3           (const Vector2<T>&);

                        /// <summary>
                        /// Copy constructor produces a Vector3, setting each element with the same value as that provided.
                        /// </summary>
                        Vector3           (const Vector3<T>&);

                        /// <summary>
                        /// Constructs a Vector3, setting each element repsectively with the first two elements of the provided array.
                        /// </summary>
                        Vector3           (const T*);

              operator  const T*          ();

    T&        operator  []                (const size_t);

    bool      operator  ==                (const Vector3<T>&) const;
    bool      operator  !=                (const Vector3<T>&) const;

    bool      operator  <                 (const Vector3<T>&) const;
    bool      operator  >                 (const Vector3<T>&) const;

    Vector3   operator  +                 (const Vector3<T>&) const;
    Vector3   operator  -                 (const Vector3<T>&) const;
    Vector3   operator  *                 (const T&) const;
    Vector3   operator  /                 (const T&) const;
    Vector3   operator  *                 (const Vector3<T>&) const;
    Vector3   operator  /                 (const Vector3<T>&) const;
    Vector3&  operator  =                 (const Vector3<T>&);

    Vector3&  operator  +=                (const Vector3<T>&);
    Vector3&  operator  -=                (const Vector3<T>&);
    Vector3&  operator  *=                (const T&);
    Vector3&  operator  /=                (const T&);
    Vector3&  operator  *=                (const Vector3<T>&);
    Vector3&  operator  /=                (const Vector3<T>&);

    /// <summary>
    /// Produces a copy of the Vector3 in a normalised state.
    /// </summary>
    Vector3             normalised        () const;
    
    /// <summary>
    /// Converts the Vector3 to a normalised state.
    /// </summary>
    Vector3&            normalise         ();

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
    T                   dot               (const Vector3<T>&) const;

    /// <summary>
    /// Calculates the dot product between the provided vectors.
    /// </summary>
    /// <params name = "l">The left hand vector to be used as part of the dot product.</params>
    /// <params name = "r">The right hand vector to be used as part of the dot product.</params>
    static T            dot               (const Vector3<T>&, const Vector3<T>&);

    /// <summary>
    /// Calculates the angle against the provided vector.
    /// </summary>
    /// <params name = "o">The other vector to get the angle from.</params>
    double              angle             (const Vector3<T>&) const;

    /// <summary>
    /// Calculates the angle between the provided vectors.
    /// </summary>
    /// <params name = "l">The left hand vector to get the angle from.</params>
    /// <params name = "r">The right hand vector to get the angle from.</params>
    static double       angle             (const Vector3<T>&, const Vector3<T>&);
  };

  MATH_TYPES(Vector3)

  template <typename T>
  Vector3<T> Vector3<T>::zero = Vector3<T>(0, 0, 0);

  template <typename T>
  Vector3<T> Vector3<T>::up = Vector3<T>(0, 1, 0);

  template <typename T>
  Vector3<T> Vector3<T>::down = Vector3<T>(0, -1, 0);

  template <typename T>
  Vector3<T> Vector3<T>::left = Vector3<T>(-1, 0, 0);

  template <typename T>
  Vector3<T> Vector3<T>::right = Vector3<T>(1, 0, 0);

  template <typename T>
  Vector3<T> Vector3<T>::forward = Vector3<T>(0, 0, 1);

  template <typename T>
  Vector3<T> Vector3<T>::backward = Vector3<T>(0, 0, -1);

  template <typename T>
  Vector3<T>::Vector3(const T& val) {
    x = val;
    y = val;
    z = val;
  }

  template <typename T>
  Vector3<T>::Vector3(const T& x, const T& y, const T& z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  template <typename T>
  Vector3<T>::Vector3(const Vector2<T>& val) {
    this->x = val.x;
    this->y = val.y;
  }

  template <typename T>
  Vector3<T>::Vector3(const Vector3<T>& val) {
    *this = val;
  }

  template <typename T>
  Vector3<T>::Vector3(const T* val) {
    x = val[0];
    y = val[1];
    z = val[2];
  }

  template <typename T>
  Vector3<T>::operator const T* () {
    return &x;
  }

  template <typename T>
  T& Vector3<T>::operator[](const size_t idx) {
    switch(idx) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        throw std::out_of_range("Index out of bounds");
    }
  }

  template <>
  bool Vector3<float>::operator == (const Vector3<float>& o) const;

  template <>
  bool Vector3<double>::operator == (const Vector3<double>& o) const;

  template <typename T>
  bool Vector3<T>::operator == (const Vector3<T>& o) const {
    return x == o.x && y == o.y && z == o.z;
  }

  template <typename T>
  bool Vector3<T>::operator != (const Vector3<T>& o) const {
    return x != o.x || y != o.y || z != o.z;
  }

  template <typename T>
  bool Vector3<T>::operator < (const Vector3<T>& o) const {
    return magnitudeSquared() < o.magnitudeSquared();
  }

  template <typename T>
  bool Vector3<T>::operator > (const Vector3<T>& o) const {
    return magnitudeSquared() > o.magnitudeSquared();
  }

  template <typename T>
  Vector3<T> Vector3<T>::operator + (const Vector3<T>& o) const {
    return Vector3(x + o.x, y + o.y, z + o.z);
  }

  template <typename T>
  Vector3<T> Vector3<T>::operator - (const Vector3<T>& o) const {
    return Vector3(x - o.x, y - o.y, z - o.z);
  }

  template <typename T>
  Vector3<T> Vector3<T>::operator * (const T& v) const {
    return Vector3(x * v, y * v, z * v);
  }

  template <typename T>
  Vector3<T> Vector3<T>::operator / (const T& v) const {
    if(v == 0)
      throw std::overflow_error("Divide by zero exception");
    return Vector3(x / v, y / v, z / v);
  }

  template <typename T>
  Vector3<T> Vector3<T>::operator * (const Vector3<T>& o) const {
    return Vector3(x * o.x, y * o.y, z * o.z);
  }

  template <typename T>
  Vector3<T> Vector3<T>::operator / (const Vector3<T>& o) const {
    if(o.x == 0 || o.y == 0 || o.z == 0)
      throw std::overflow_error("Divide by zero exception");
    return Vector3(x / o.x, y / o.y, z / o.z);
  }

  template <typename T>
  Vector3<T>& Vector3<T>::operator = (const Vector3<T>& o) {
    x = o.x;
    y = o.y;
    z = o.z;
    return *this;
  }

  template <typename T>
  Vector3<T>& Vector3<T>::operator += (const Vector3<T>& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
  }

  template <typename T>
  Vector3<T>& Vector3<T>::operator -= (const Vector3<T>& o) {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
  }

  template <typename T>
  Vector3<T>& Vector3<T>::operator *= (const T& v) {
    x *= v;
    y *= v;
    z *= v;
    return *this;
  }

  template <typename T>
  Vector3<T>& Vector3<T>::operator /= (const T& v) {
    if(v == 0)
      throw std::overflow_error("Divide by zero exception");
    x /= v;
    y /= v;
    z /= v;
    return *this;
  }

  template <typename T>
  Vector3<T>& Vector3<T>::operator *= (const Vector3<T>& o) {
    x *= o.x;
    y *= o.y;
    z *= o.z;
    return *this;
  }

  template <typename T>
  Vector3<T>& Vector3<T>::operator /= (const Vector3<T>& o) {
    if(o.x == 0 || o.y == 0)
      throw std::overflow_error("Divide by zero exception");
    x /= o.x;
    y /= o.y;
    z /= o.z;
    return *this;
  }

  template <typename T>
  Vector3<T> Vector3<T>::normalised() const {
    return *this / magnitude();
  }

  template <>
  Vector3<int>& Vector3<int>::normalise();

  template <>
  Vector3<unsigned int>& Vector3<unsigned int>::normalise();

  template <typename T>
  Vector3<T>& Vector3<T>::normalise() {
    *this /= magnitude();
    return *this;
  }

  template <typename T>
  double Vector3<T>::magnitude() const {
    return sqrt(magnitudeSquared());
  }

  template <typename T>
  double Vector3<T>::magnitudeSquared() const {
    return (double)((x * x) + (y * y) + (z * z));
  }

  template <typename T>
  T Vector3<T>::dot(const Vector3<T>& o) const {
    return (x * o.x) + (y * o.y) + (z * o.z);
  }

  template <typename T>
  T Vector3<T>::dot(const Vector3<T>& l, const Vector3<T>& r) {
    return l.dot(r);
  }

  template <typename T>
  double Vector3<T>::angle(const Vector3<T>& o) const {
    return acos(dot(o) / (magnitude() * o.magnitude()));
  }

  template <typename T>
  double Vector3<T>::angle(const Vector3<T>& l, const Vector3<T>& r) {
    return l.angle(r);
  }

}