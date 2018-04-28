#pragma once

#include "Matrix.h"

namespace DTU {

  template <typename T>
  struct Matrix2 : public Matrix<T, 2, 2> {
                                  /// <summary>
                                  /// Constructs an identity Matrix2x2.
                                  /// </summary>
                                  Matrix2             ();

                                  /// <summary>
                                  /// Constructs a Matrix2x2, setting elements along the diagonal with the provided value.
                                  /// </summary>
                                  Matrix2             (const T&);

                                  /// <summary>
                                  /// Constructs a Matrix2x2, setting each element repsectively with the arguments provided.
                                  /// </summary>
                                  template <typename ... V>
                                  Matrix2             (const T&, V...);

                                  /// <summary>
                                  /// Copy constructor produces a Matrix2x2, setting each element with the same value as that provided.
                                  /// </summary>
                                  template <typename S, size_t V, size_t U>
                                  Matrix2             (const Matrix<S, V, U>&);

                                  /// <summary>
                                  /// Constructs a Matrix2x2, setting each element repsectively with the elements of the provided array.
                                  /// </summary>
                                  Matrix2             (const T*);
    
    /// <summary>
    /// Checks whether the Matrix2 is symmetrical.
    /// </summary>
    const bool                    Symmetric           () const;

    /// <summar>
    /// Gets the determinant of the Matrix2.
    /// </summar>
    const T                       Determinant         () const;

    /// <summary>
    /// Transposes the Matrix2. Mirroring each value along the diagonal.
    /// </summary>
    Matrix2&                      transpose           ();

    /// <summary>
    /// Inverse the Matrix2.
    /// </summary>
    Matrix2&                      inverse             ();

    /// <summary>
    /// Produces an inversed copy of the Matrix2.
    /// </summary>
    Matrix2                       inversed            () const;
  };

  MATH_TYPES(Matrix2)

  template <typename T>
  Matrix2<T>::Matrix2() : Matrix2<T>(1.0f) { }

  template <typename T>
  Matrix2<T>::Matrix2(const T& val) {
    this->m_data[0][0] = val;
     this->m_data[1][1] = val;
  }

  template <typename T>
  template <typename ... V>
  Matrix2<T>::Matrix2(const T& val, V... args) : Matrix<T, 2, 2>(val, args...) { }

  template <typename T>
  template <typename S, size_t V, size_t U>
  Matrix2<T>::Matrix2(const Matrix<S, V, U>& o) : Matrix<T, 2, 2>(o) {}

  template <typename T>
  Matrix2<T>::Matrix2(const T* o) : Matrix<T, 2, 2>(o) {}

  template <typename T>
  const bool Matrix2<T>::Symmetric() const {
    return this->m_data[0][1] == this->m_data[1][0];
  }
  template <typename T>
  const T Matrix2<T>::Determinant() const {
    return  (this->m_data[0][0] * this->m_data[1][1])
            - (this->m_data[0][1] * this->m_data[1][0]);
  }

  template <typename T>
  Matrix2<T>& Matrix2<T>::transpose() {
    *this = this->transposed();
    return *this;
  }

  template <typename T>
  Matrix2<T>& Matrix2<T>::inverse() {
    *this = this->inversed();
    return *this;
  }

  template <typename T>
  Matrix2<T> Matrix2<T>::inversed() const {
    Matrix2 m;
    m[0][0] =  this[1][1];
    m[0][1] = -this[0][1];
    m[1][0] = -this[1][0];
    m[1][1] =  this[0][0];
    return m / Determinant();
  }

}