#pragma once

#include "Matrix2.h"

namespace DTU {

  template <typename T>
  struct Matrix3 : public Matrix<T, 3, 3> {
                                  /// <summary>
                                  /// Constructs an identity Matrix3x3.
                                  /// </summary>
                                  Matrix3             ();

                                  /// <summary>
                                  /// Constructs a Matrix3x3, setting elements along the diagonal with the provided value.
                                  /// </summary>
                                  Matrix3             (const T&);

                                  /// <summary>
                                  /// Constructs a Matrix3x3, setting each element repsectively with the arguments provided.
                                  /// </summary>
                                  template <typename ... V>
                                  Matrix3             (const T&, V...);

                                  /// <summary>
                                  /// Copy constructor produces a Matrix3x3, setting each element with the same value as that provided.
                                  /// </summary>
                                  template <typename S, size_t V, size_t U>
                                  Matrix3             (const Matrix<S, V, U>&);

                                  /// <summary>
                                  /// Constructs a Matrix3x3, setting each element repsectively with the elements of the provided array.
                                  /// </summary>
                                  Matrix3             (const T*);
    
    /// <summary>
    /// Checks whether the Matrix3 is symmetrical.
    /// </summary>
    const bool                    Symmetric           () const;

    /// <summar>
    /// Gets the determinant of the Matrix3.
    /// </summar>
    const T                       Determinant         () const;

    /// <summary>
    /// Transposes the Matrix3. Mirroring each value along the diagonal.
    /// </summary>
    Matrix3&                      transpose           ();
  };

  MATH_TYPES(Matrix3)

  template <typename T>
  Matrix3<T>::Matrix3() : Matrix3<T>(1.0f) { }

  template <typename T>
  Matrix3<T>::Matrix3(const T& val) {
    this->m_data[0][0] = val;
    this->m_data[1][1] = val;
    this->m_data[2][2] = val;
  }

  template <typename T>
  template <typename ... V>
  Matrix3<T>::Matrix3(const T& val, V... args) : Matrix<T, 3, 3>(val, args...) { }

  template <typename T>
  template <typename S, size_t V, size_t U>
  Matrix3<T>::Matrix3(const Matrix<S, V, U>& o) : Matrix<T, 3, 3>(o) {}

  template <typename T>
  Matrix3<T>::Matrix3(const T* o) : Matrix<T, 3, 3>(o) {}

  template <typename T>
  const bool Matrix3<T>::Symmetric() const {
    for(size_t y = 0; y < 3; ++y)
    for(size_t x = y + 1; x < 3; ++x)
      if(this->m_data[y][x] != this->m_data[x][y])
        return false;
    return true;
  }
  template <typename T>
  const T Matrix3<T>::Determinant() const {
    return (this->m_data[0][0] * Matrix2<T>(this->m_data[1][1], this->m_data[1][2], this->m_data[2][1], this->m_data[2][2]).Determinant())
            - (this->m_data[0][1] * Matrix2<T>(this->m_data[1][0], this->m_data[1][2], this->m_data[2][0], this->m_data[2][2]).Determinant())
            + (this->m_data[0][2] * Matrix2<T>(this->m_data[1][0], this->m_data[1][1], this->m_data[2][0], this->m_data[2][1]).Determinant());
  }

  template <typename T>
  Matrix3<T>& Matrix3<T>::transpose() {
    *this = this->transposed();
    return *this;
  }

}