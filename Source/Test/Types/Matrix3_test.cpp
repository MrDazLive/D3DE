#include "declerations.h"

#include <Types/Matrix.h>

using namespace DTU;

namespace Types_Test {
  void Matrix3::Reset() {}

  void Matrix3::Examine() {
    TestCase([]() {
      Matrix3f m(1.0f);
      return m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f
          && m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f;
    }, "Matrix3()");

    TestCase([]() {
      Matrix2f n(1.0f);
      Matrix3f m(n);
      return m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f
          && m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 0.0f;
    }, "Matrix3(const MatrixN&)");

    TestCase([]() {
      Matrix2x3f n;
      n[0][1] = 1.3f;
      Matrix3f m(n);
      return m[0][0] == 0.0f && m[0][1] == 1.3f && m[0][2] == 0.0f
          && m[1][0] == 0.0f && m[1][1] == 0.0f && m[1][2] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 0.0f;
    }, "Matrix3(const MatrixXxY&)");

    TestCase([]() {
      float n[3][3] = {
        { 0.0f, 0.0f, 0.0f },
        { 1.3f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
      };
      Matrix3f m(&n[0][0]);
      return m[0][0] == 0.0f && m[0][1] == 0.0f && m[0][2] == 0.0f
          && m[1][0] == 1.3f && m[1][1] == 0.0f && m[1][2] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 0.0f;
    }, "Matrix3(const T*)");

    TestCase([]() {
      Matrix3f n(1.0f);
      Matrix3f m(1.0f);
      return n == m;
    }, "Matrix3==(const MatrixN&)");

    TestCase([]() {
      Matrix2f n(1.0f);
      Matrix3f m(1.0f);
      return n != m;
    }, "Matrix3!=(const MatrixN&)");

    TestCase([]() {
      float m_[3][3] = {{1,2,1}, {0,2,0}, {2,0,1}};
      Matrix3f m(&m_[0][0]);
      float n_[3][3] = {{1,2,1}, {2,2,0}, {0,1,0}};
      Matrix3f n(&n_[0][0]);

      float o_[3][3] = {{5,7,1}, {4,4,0}, {2,5,2}};
      Matrix3f o(&o_[0][0]);

      return m * n == o;
    }, "Matrix3*(const MatrixN&)");

    TestCase([]() {
      float m_[3][3] = {{1,2,1}, {0,2,0}, {2,0,1}};
      Matrix3f m(&m_[0][0]);
      float n_[3][2] = {{1,2}, {2,2}, {0,1}};
      Matrix3x2f n(&n_[0][0]);

      float o_[3][2] = {{5,7}, {4,4}, {2,5}};
      Matrix3x2f o(&o_[0][0]);

      return m * n == o;
    }, "Matrix3*(const MatrixXxY&)");

    TestCase([]() {
      float m_[3][3] = {{1,2,1}, {0,2,0}, {2,0,1}};
      Matrix3f m(&m_[0][0]);

      Matrix3f n(1.0f);
      n = m;

      return n == m;
    }, "Matrix3=(const MatrixN&)");

    TestCase([]() {
      float m_[3][3] = {{1,2,1}, {0,2,0}, {2,0,1}};
      Matrix3f m(&m_[0][0]);

      float n_[3][3] = {{1,2,1}, {2,2,0}, {0,1,0}};
      m *= Matrix3f(&n_[0][0]);

      float o_[3][3] = {{5,7,1}, {4,4,0}, {2,5,2}};
      Matrix3f o(&o_[0][0]);

      return m == o;
    }, "Matrix3*=(const MatrixN&)");

    TestCase([]() {
      float m_[3][3] = {{1,2,1}, {2,4,0}, {1,0,1}};
      Matrix3f m(&m_[0][0]);

      return m.Symmetric();
    }, "Matrix3::Symmetric");

    TestCase([]() {
      float m_[3][3] = {{1,2,1}, {0,2,0}, {2,0,1}};
      Matrix3f m(&m_[0][0]);
      Matrix3f n(&m_[0][0]);

      Matrix3f t = n.transposed();

      float o_[3][3] = {{1,0,2}, {2,2,0}, {1,0,1}};
      Matrix3f o(&o_[0][0]);

      return m == n && t == o;
    }, "Matrix3::transposed");

    TestCase([]() {
      float m_[3][3] = {{1,2,1}, {0,2,0}, {2,0,1}};
      Matrix3f m(&m_[0][0]);
      m.transpose();

      float o_[3][3] = {{1,0,2}, {2,2,0}, {1,0,1}};
      Matrix3f o(&o_[0][0]);

      return m == o;
    }, "Matrix3::transpose");

    TestCase([]() {
      float m_[3][3] = {{3,0,4}, {0,2,0}, {6,8,0}};
      Matrix3f m(&m_[0][0]);
      m.normaliseEigenvectors();

      float o_[3][3] = {{0.6f,0.0f,0.8f}, {0.0f,1.0f,0.0f}, {0.6f,0.8f,0.0f}};
      Matrix3f o(&o_[0][0]);

      return m == o;
    }, "Matrix3::normaliseEigenvectors");
  }
}