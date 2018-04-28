#pragma once

#include "Matrix3.h"

namespace DTU {

  template <typename T>
  struct Matrix4 : public Matrix<T, 4, 4> {
                                  /// <summary>
                                  /// Constructs an identity Matrix4x4.
                                  /// </summary>
                                  Matrix4             ();

                                  /// <summary>
                                  /// Constructs a Matrix4x4, setting elements along the diagonal with the provided value.
                                  /// </summary>
                                  Matrix4             (const T&);

                                  /// <summary>
                                  /// Constructs a Matrix4x4, setting each element repsectively with the arguments provided.
                                  /// </summary>
                                  template <typename ... V>
                                  Matrix4             (const T&, V...);

                                  /// <summary>
                                  /// Copy constructor produces a Matrix4x4, setting each element with the same value as that provided.
                                  /// </summary>
                                  template <typename S, size_t V, size_t U>
                                  Matrix4             (const Matrix<S, V, U>&);

                                  /// <summary>
                                  /// Constructs a Matrix4x3, setting each element repsectively with the elements of the provided array.
                                  /// </summary>
                                  Matrix4             (const T*);
    
    /// <summary>
    /// Checks whether the Matrix4 is symmetrical.
    /// </summary>
    const bool                    Symmetric           () const;

    /// <summar>
    /// Gets the determinant of the Matrix4.
    /// </summar>
    const T                       Determinant         () const;

    /// <summary>
    /// Transposes the Matrix4. Mirroring each value along the diagonal.
    /// </summary>
    Matrix4&                      transpose           ();

    /// <summary>
    /// Inverse the Matrix4.
    /// </summary>
    Matrix4&                      inverse();

    /// <summary>
    /// Produces an inversed copy of the Matrix4.
    /// </summary>
    Matrix4                       inversed() const;
  };

  MATH_TYPES(Matrix4)

  template <typename T>
  Matrix4<T>::Matrix4() : Matrix4<T>(1.0f) { }

  template <typename T>
  Matrix4<T>::Matrix4(const T& val) {
    this->m_data[0][0] = val;
    this->m_data[1][1] = val;
    this->m_data[2][2] = val;
    this->m_data[3][3] = val;
  }

  template <typename T>
  template <typename ... V>
  Matrix4<T>::Matrix4(const T& val, V... args) : Matrix<T, 4, 4>(val, args...) { }

  template <typename T>
  template <typename S, size_t V, size_t U>
  Matrix4<T>::Matrix4(const Matrix<S, V, U>& o) : Matrix<T, 4, 4>(o) {}

  template <typename T>
  Matrix4<T>::Matrix4(const T* o) : Matrix<T, 4, 4>(o) {}

  template <typename T>
  const bool Matrix4<T>::Symmetric() const {
    for(size_t y = 0; y < 4; ++y)
    for(size_t x = y + 1; x < 4; ++x)
      if(this->m_data[y][x] != this->m_data[x][y])
        return false;
    return true;
  }
  template <typename T>
  const T Matrix4<T>::Determinant() const {
    auto data = this->m_data;
    return (data[0][0] * Matrix3<T>(data[1][1], data[1][2], data[1][3], data[2][1], data[2][2], data[2][3], data[3][1], data[3][2], data[3][3]).Determinant())
            - (data[0][1] * Matrix3<T>(data[1][0], data[1][2], data[1][3], data[2][0], data[2][2], data[2][3], data[3][0], data[3][2], data[3][3]).Determinant())
            + (data[0][2] * Matrix3<T>(data[1][0], data[1][1], data[1][3], data[2][0], data[2][1], data[2][3], data[3][0], data[3][1], data[3][3]).Determinant())
            - (data[0][3] * Matrix3<T>(data[1][0], data[1][1], data[1][2], data[2][0], data[2][1], data[2][2], data[3][0], data[3][1], data[3][2]).Determinant());
  }

  template <typename T>
  Matrix4<T>& Matrix4<T>::transpose() {
    *this = this->transposed();
    return *this;
  }

  template <typename T>
  Matrix4<T>& Matrix4<T>::inverse() {
    *this = this->inversed();
    return *this;
  }

  template <typename T>
  Matrix4<T> Matrix4<T>::inversed() const {
    Matrix4 m;
    auto data = this->m_data;

    m[0][0] =  Matrix3<T>(data[1][1], data[1][2], data[1][3], data[2][1], data[2][2], data[2][3], data[3][1], data[3][2], data[3][3]).Determinant();
    m[0][1] = -Matrix3<T>(data[1][0], data[1][2], data[1][3], data[2][0], data[2][2], data[2][3], data[3][0], data[3][2], data[3][3]).Determinant();
    m[0][2] =  Matrix3<T>(data[1][0], data[1][1], data[1][3], data[2][0], data[2][1], data[2][3], data[3][0], data[3][1], data[3][3]).Determinant();
    m[0][3] = -Matrix3<T>(data[1][0], data[1][1], data[1][1], data[2][0], data[2][1], data[2][2], data[3][0], data[3][1], data[3][2]).Determinant();

    m[1][0] = -Matrix3<T>(data[0][1], data[0][2], data[0][3], data[2][1], data[2][2], data[2][3], data[3][1], data[3][2], data[3][3]).Determinant();
    m[1][1] =  Matrix3<T>(data[0][0], data[0][2], data[0][3], data[2][0], data[2][2], data[2][3], data[3][0], data[3][2], data[3][3]).Determinant();
    m[1][2] = -Matrix3<T>(data[0][0], data[0][1], data[0][3], data[2][0], data[2][1], data[2][3], data[3][0], data[3][1], data[3][3]).Determinant();
    m[1][3] =  Matrix3<T>(data[0][0], data[0][1], data[0][1], data[2][0], data[2][1], data[2][2], data[3][0], data[3][1], data[3][2]).Determinant();

    m[2][0] =  Matrix3<T>(data[0][1], data[0][2], data[0][3], data[1][1], data[1][2], data[1][3], data[3][1], data[3][2], data[3][3]).Determinant();
    m[2][1] = -Matrix3<T>(data[0][0], data[0][2], data[0][3], data[1][0], data[1][2], data[1][3], data[3][0], data[3][2], data[3][3]).Determinant();
    m[2][2] =  Matrix3<T>(data[0][0], data[0][1], data[0][3], data[1][0], data[1][1], data[1][3], data[3][0], data[3][1], data[3][3]).Determinant();
    m[2][3] = -Matrix3<T>(data[0][0], data[0][1], data[0][1], data[1][0], data[1][1], data[1][2], data[3][0], data[3][1], data[3][2]).Determinant();

    m[3][0] = -Matrix3<T>(data[0][1], data[0][2], data[0][3], data[1][1], data[1][2], data[1][3], data[2][1], data[2][2], data[2][3]).Determinant();
    m[3][1] =  Matrix3<T>(data[0][0], data[0][2], data[0][3], data[1][0], data[1][2], data[1][3], data[2][0], data[2][2], data[2][3]).Determinant();
    m[3][2] = -Matrix3<T>(data[0][0], data[0][1], data[0][3], data[1][0], data[1][1], data[1][3], data[2][0], data[2][1], data[2][3]).Determinant();
    m[3][3] =  Matrix3<T>(data[0][0], data[0][1], data[0][1], data[1][0], data[1][1], data[1][2], data[2][0], data[2][1], data[2][2]).Determinant();

    T d = (data[0][0] * m[0][0])
      + (data[0][1] * m[0][1])
      + (data[0][2] * m[0][2]);

    return m.transposed() / d;
  }

}