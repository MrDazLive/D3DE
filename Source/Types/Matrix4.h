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
    return (this->m_data[0][0] * Matrix3<T>(this->m_data[1][1], this->m_data[1][2], this->m_data[1][3], this->m_data[2][1], this->m_data[2][2], this->m_data[2][3], this->m_data[3][1], this->m_data[3][2], this->m_data[3][3]).Determinant())
            - (this->m_data[1][1] * Matrix3<T>(this->m_data[1][0], this->m_data[1][2], this->m_data[1][3], this->m_data[2][0], this->m_data[2][2], this->m_data[2][3], this->m_data[3][0], this->m_data[3][2], this->m_data[3][3]).Determinant())
            + (this->m_data[2][2] * Matrix3<T>(this->m_data[1][0], this->m_data[1][1], this->m_data[1][3], this->m_data[2][0], this->m_data[2][1], this->m_data[2][3], this->m_data[3][0], this->m_data[3][1], this->m_data[3][3]).Determinant())
            - (this->m_data[3][3] * Matrix3<T>(this->m_data[1][0], this->m_data[1][1], this->m_data[1][2], this->m_data[2][0], this->m_data[2][1], this->m_data[2][2], this->m_data[3][0], this->m_data[3][1], this->m_data[3][2]).Determinant());
  }

  template <typename T>
  Matrix4<T>& Matrix4<T>::transpose() {
    *this = this->transposed();
    return *this;
  }

}