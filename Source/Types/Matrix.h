#pragma once

#include "defines.h"

namespace DTU {

  template <typename T, size_t Y, size_t X>
  struct Matrix {
  private:
    T                             m_data[Y][X]          {{ 0 }};
  public:
                                  /// <summary>
                                  /// Default constructor.
                                  /// </summary>
                                  Matrix                () = default;

                                  /// <summary>
                                  /// Constructs a matrix, setting elements along the diagonal with the provided value.
                                  /// </summary>
                                  Matrix                (const T&);

                                  /// <summary>
                                  /// Copy constructor produces a Matrix, setting each element with the same value as that provided.
                                  /// </summary>
                                  template<size_t V, size_t U>
                                  Matrix                (const Matrix<T, V, U>&);

                                  /// <summary>
                                  /// Constructs a Matrix, setting each element repsectively with the elements of the provided array.
                                  /// </summary>
                                  Matrix                (const T*);

                      operator    T* const              ();
    T* const          operator    []                    (const size_t) const;

    template<size_t V, size_t U> 
    bool              operator    ==                    (const Matrix<T, V, U>&) const;
    template<size_t V, size_t U> 
    bool              operator    !=                    (const Matrix<T, V, U>&) const;
    
    template<size_t V, size_t U> 
    Matrix<T, Y, U>   operator    *                     (const Matrix<T, V, U>&) const;
    Matrix&           operator    =                     (const Matrix<T, Y, X>&);

    template<size_t U> 
    Matrix&           operator    *=                    (const Matrix<T, X, U>&);

    /// <summary>
    /// Gets the row count of the matrix.
    /// </summary>
    const size_t                  Rows                  () const { return Y; }
    
    /// <summary>
    /// Gets the column count of the matrix.
    /// </summary>
    const size_t                  Columns               () const { return X; }
    
    /// <summary>
    /// Checks whether the matrix is square.
    /// </summary>
    const bool                    Square                () const { return X == Y; }
    
    /// <summary>
    /// Checks whether the matrix is symmetrical.
    /// </summary>
    const bool                    Symmetric             () const;

    /// <summary>
    /// Produces a transposed copy of the matrix. Mirroring each value along the diagonal.
    /// </summary>
    Matrix<T, X, Y>               transposed            () const;

    /// <summary>
    /// Transposes the Matrix. Mirroring each value along the diagonal.
    /// </summary>
    Matrix&                       transpose             ();

    /// <summary>
    /// Normalises each row in the matrix independently.
    /// </summary>
    Matrix&                       normaliseEigenvectors ();
  };

  #define MATRIX_DEF(X, Y)                    \
    template <typename T>                     \
    using Matrix##X##x##Y = Matrix<T, X, Y>;  \
    MATH_TYPES(Matrix##X##x##Y)               \

  #define SQAURE_MATRIX_DEF(S)            \
    template <typename T>                 \
    using Matrix##S = Matrix<T, S, S>;    \
    MATH_TYPES(Matrix##S)                 \
    MATRIX_DEF(S, S)                      \

  MATRIX_DEF(2, 3)
  MATRIX_DEF(3, 2)
  MATRIX_DEF(3, 4)
  MATRIX_DEF(4, 3)
  SQAURE_MATRIX_DEF(2)
  SQAURE_MATRIX_DEF(3)
  SQAURE_MATRIX_DEF(4)

  template <typename T, size_t Y, size_t X>
  Matrix<T, Y, X>::Matrix(const T& val) {
    const size_t min = X < Y ? X : Y;
    for(size_t idx = 0; idx < min; ++idx)
      m_data[idx][idx] = val;
  }

  template <typename T, size_t Y, size_t X>
  template <size_t V, size_t U>
  Matrix<T, Y, X>::Matrix(const Matrix<T, V, U>& o) {
    const size_t min_y = V < Y ? V : Y;
    const size_t min_x = U < X ? U : X;
    for(size_t y = 0; y < min_y; ++y)
    for(size_t x = 0; x < min_x; ++x)
      m_data[y][x] = o[y][x];
  }

  template <typename T, size_t Y, size_t X>
  Matrix<T, Y, X>::Matrix(const T* o) {
    size_t idx = 0;
    for(size_t y = 0; y < Y; ++y)
    for(size_t x = 0; x < X; ++x, ++idx)
      m_data[y][x] = o[idx];
  }

  template <typename T, size_t Y, size_t X>
  Matrix<T, Y, X>::operator T* const () {
    return &m_data[0][0];
  }

  template <typename T, size_t Y, size_t X>
  T* const Matrix<T, Y, X>::operator [] (const size_t idx) const {
    return (T*)m_data[idx];
  }

  template <typename T, size_t Y, size_t X>
  template <size_t V, size_t U>
  bool Matrix<T, Y, X>::operator == (const Matrix<T, V, U>& o) const {
    if(Y != V || X != U)
      return false;
      
    for(size_t y = 0; y < Y; ++y)
    for(size_t x = 0; x < X; ++x)
      if(m_data[y][x] != o[y][x])
        return false;
    return true;
  }

  template <typename T, size_t Y, size_t X>
  template <size_t V, size_t U>
  bool Matrix<T, Y, X>::operator != (const Matrix<T, V, U>& o) const {
    if(Y != V || X != U)
      return true;
      
    for(size_t y = 0; y < Y; ++y)
    for(size_t x = 0; x < X; ++x)
      if(m_data[y][x] != o[y][x])
        return true;
    return false;
  }

  template <typename T, size_t Y, size_t X>
  template<size_t V, size_t U> 
  Matrix<T, Y, U> Matrix<T, Y, X>::operator * (const Matrix<T, V, U>& o) const {
    if(X != V)
      throw std::logic_error("Matrices incompatible for multiplication");

    Matrix<T, Y, U> matrix;
    for(size_t y = 0; y < Y; ++y)
    for(size_t x = 0; x < U; ++x)
    for(size_t a = 0; a < V; ++a)
      matrix[y][x] += m_data[y][a] * o[a][x];
    return matrix;
  }

  template <typename T, size_t Y, size_t X>
  Matrix<T, Y, X>& Matrix<T, Y, X>::operator = (const Matrix<T, Y, X>& o) {
    for(size_t y = 0; y < Y; ++y)
    for(size_t x = 0; x < X; ++x)
      m_data[y][x] = o[y][x];
    return *this;
  }

  template <typename T, size_t Y, size_t X>
  template<size_t U> 
  Matrix<T, Y, X>& Matrix<T, Y, X>::operator *= (const Matrix<T, X, U>& o) {
    *this = *this * o;
    return *this;
  }

  template <typename T, size_t Y, size_t X>
  const bool Matrix<T, Y, X>::Symmetric() const {
    if(!Square())
      throw std::logic_error("Invalid method for non-square matrix");

    for(size_t y = 0; y < Y; ++y)
    for(size_t x = y; x < X; ++x)
      if(m_data[y][x] != m_data[x][y])
        return false;
    return true;
  }

  template <typename T, size_t Y, size_t X>
  Matrix<T, X, Y> Matrix<T, Y, X>::transposed() const {
    Matrix<T, X, Y> matrix;
    for(size_t y = 0; y < Y; ++y)
    for(size_t x = 0; x < X; ++x)
      matrix[x][y] = m_data[y][x];
    return matrix;
  }

  template <typename T, size_t Y, size_t X>
  Matrix<T, Y, X>& Matrix<T, Y, X>::Matrix::transpose() {
    if(!Square())
      throw std::logic_error("Invalid method for non-square matrix");

    *this = transposed();
    return *this;
  }

  template <typename T, size_t Y, size_t X>
  Matrix<T, Y, X>& Matrix<T, Y, X>::normaliseEigenvectors() {
    for(size_t y = 0; y < Y; ++y) {
      T row = 0;
      for(size_t x = 0; x < X; ++x)
        row += m_data[y][x] * m_data[y][x];
      row = sqrt(row);
      for(size_t x = 0; x < X; ++x)
        m_data[y][x] /= row;
    }
    return *this;
  }

}