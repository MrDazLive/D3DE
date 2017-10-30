#include "declerations.h"

#include <Types/Matrix.h>

using namespace DTU;

namespace Types_Test {
  void Matrix3x4::Reset() {}

  void Matrix3x4::Examine() {
    TestCase([]() {
      Matrix3x4f m;
      return m[0][0] == 0.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f
          && m[1][0] == 0.0f && m[1][1] == 0.0f && m[1][2] == 0.0f && m[1][3] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 0.0f && m[2][3] == 0.0f;
    }, "Matrix3x4()");

    TestCase([]() {
      Matrix3f n(1.0f);
      Matrix3x4f m(n);
      return m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f
          && m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f;
    }, "Matrix3x4(const MatrixN&)");

    TestCase([]() {
      Matrix2x3f n;
      n[0][1] = 1.3f;
      Matrix3x4f m(n);
      return m[0][0] == 0.0f && m[0][1] == 1.3f && m[0][2] == 0.0f && m[0][3] == 0.0f
          && m[1][0] == 0.0f && m[1][1] == 0.0f && m[1][2] == 0.0f && m[1][3] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 0.0f && m[2][3] == 0.0f;
    }, "Matrix3x4(const MatrixXxY&)");

    TestCase([]() {
      float n[3][4] = {
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 1.3f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f }
      };
      Matrix3x4f m(&n[0][0]);
      return m[0][0] == 0.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f
          && m[1][0] == 1.3f && m[1][1] == 0.0f && m[1][2] == 0.0f && m[1][3] == 0.0f
          && m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 0.0f && m[2][3] == 0.0f;
    }, "Matrix3x4(const T*)");

    TestCase([]() {
      Matrix3x4f n;
      Matrix3x4f m;
      n[0][0] = 2.0f;
      m[0][0] = 2.0f;
      return n == m;
    }, "Matrix3x4==(const MatrixXxY&)");

    TestCase([]() {
      Matrix3x4f n;
      Matrix2x3f m;
      return n != m;
    }, "Matrix3x4!=(const MatrixXxY&)");

    TestCase([]() {
      float m_[3][4] = {{1,2,1,3}, {0,2,0,2}, {2,0,1,0}};
      Matrix3x4f m(&m_[0][0]);
      float n_[4][4] = {{1,2,1,1}, {2,2,0,3}, {0,1,0,2}, {0,0,0,1}};
      Matrix4f n(&n_[0][0]);

      float o_[3][4] = {{5,7,1,12}, {4,4,0,8}, {2,5,2,4}};
      Matrix3x4f o(&o_[0][0]);

      return m * n == o;
    }, "Matrix3x4*(const MatrixN&)");

    TestCase([]() {
      float m_[3][4] = {{1,2,1,3}, {0,2,0,2}, {2,0,1,0}};
      Matrix3x4f m(&m_[0][0]);
      float n_[4][3] = {{1,2,1}, {2,2,0}, {0,1,0}, {0,0,0}};
      Matrix4x3f n(&n_[0][0]);

      float o_[3][3] = {{5,7,1}, {4,4,0}, {2,5,2}};
      Matrix3f o(&o_[0][0]);

      return m * n == o;
    }, "Matrix3x4*(const MatrixXxY&)");

    TestCase([]() {
      float m_[3][4] = {{1,2,1,3}, {0,2,0,2}, {2,0,1,0}};
      Matrix3x4f m(&m_[0][0]);

      Matrix3x4f n;
      n = m;

      return n == m;
    }, "Matrix3x4=(const MatrixXxY&)");

    TestCase([]() {
      float m_[3][4] = {{1,2,1,3}, {0,2,0,1}, {2,0,1,1}};
      Matrix3x4f m(&m_[0][0]);
      Matrix3x4f n(&m_[0][0]);

      Matrix4x3f t = n.transposed();

      float o_[4][3] = {{1,0,2}, {2,2,0}, {1,0,1}, {3,1,1}};
      Matrix4x3f o(&o_[0][0]);

      return m == n && t == o;
    }, "Matrix3x4::transposed");

    TestCase([]() {
      float m_[3][4] = {{3,0,4,0}, {0,0,2,0}, {6,0,8,0}};
      Matrix3x4f m(&m_[0][0]);
      m.normaliseEigenvectors();

      float o_[3][4] = {{0.6f,0.0f,0.8f,0.0f}, {0.0f,0.0f,1.0f,0.0f}, {0.6f,0.0f,0.8f,0.0f}};
      Matrix3x4f o(&o_[0][0]);

      return m == o;
    }, "Matrix3x4::normaliseEigenvectors");
  }
}