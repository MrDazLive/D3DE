#include "declerations.h"

#include <Types/Vector4.h>

using namespace DTU;

namespace Types_Test {
  void Vector3::Reset() {}

  void Vector3::Examine() {
    TestCase([](){
      Vector3d v;
      return v.x == 0.0 && v.y == 0.0 && v.z == 0.0;
    }, "Vector3()");
    
    TestCase([](){
      Vector3d v(1.3);
      return v.x == 1.3 && v.y == 1.3 && v.z == 1.3;
    }, "Vector3(const T&)");
    
    TestCase([](){
      Vector3d v(0.7, 0.2, 0.4);
      return v.x == 0.7 && v.y == 0.2 && v.z == 0.4;
    }, "Vector3(const T&, const T&)");
    
    TestCase([](){
      Vector2d w(0.2, 0.3);
      Vector3d v(w);
      return v.x == 0.2 && v.y == 0.3 && v.z == 0.0;
    }, "Vector3(const DTU::Vector2&)");
    
    TestCase([](){
      Vector3d w(0.2);
      Vector3d v(w);
      return v.x == 0.2 && v.y == 0.2 && v.z == 0.2;
    }, "Vector3(const DTU::Vector3&)");
    
    TestCase([](){
      Vector4d w(0.2, 0.3, 0.5, 0.8);
      Vector3d v(w);
      return v.x == 0.2 && v.y == 0.3 && v.z == 0.5;
    }, "Vector3(const DTU::Vector4&)");
    
    TestCase([](){
      double a[3] = { 0.2, 0.4, 0.5 };
      Vector3d v((const double*)a);
      return v.x == 0.2 && v.y == 0.4 && v.z == 0.5;
    }, "Vector3(const T*)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.1);
      return v[0] == 0.2 && v[1] == 0.4 && v[2] == 0.1;
    }, "Vector3[]");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.1);
      return v == Vector3d(0.2, 0.4, 0.1);
    }, "Vector3==(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.7, 0.2, 0.2);
      return v != Vector3d(0.3, 0.2, 0.2);
    }, "Vector3!=(const DTU::Vector3&");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.4);
      return v + Vector3d(0.2, 0.3, 0.1) == Vector3d(0.4, 0.7, 0.5);
    }, "Vector3+(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.4);
      return v - Vector3d(0.1, 0.0, 0.3) == Vector3d(0.1, 0.4, 0.7);
    }, "Vector3-(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.2);
      return v * 2 == Vector3d(0.4, 0.8, 0.4);
    }, "Vector3*(const T&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.7);
      return v / 2 == Vector3d(0.1, 0.2, 0.35);
    }, "Vector3/(const T&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.1);
      Vector3d w(2.0, 3.0, 1.0);
      return (v * w) == Vector3d(0.4, 1.2, 0.1);
    }, "Vector3*(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.3);
      Vector3d w(4, 2, 2);
      return (v / w) == Vector3d(0.05, 0.2, 0.15);
    }, "Vector3/(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.2);
      v = 0.1;
      return v == Vector3d(0.1, 0.1, 0.1);
    }, "Vector3=(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.0);
      v += Vector3d(0.2, 0.3, 0.1);
      return v == Vector3d(0.4, 0.7, 0.1);
    }, "Vector3+=(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.1);
      v -= Vector3d(0.1, 0.0, 0.1);
      return v == Vector3d(0.1, 0.4, 0.0);
    }, "Vector3-=(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.0);
      v *= 2;
      return v == Vector3d(0.4, 0.8, 0.0);
    }, "Vector3*=(const T&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.8);
      v /= 2;
      return v == Vector3d(0.1, 0.2, 0.4);
    }, "Vector3/=(const T&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 1.0);
      v *= Vector3d(2.0, 3.0, 5.0);
      return v == Vector3d(0.4, 1.2, 5.0);
    }, "Vector3*=(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(0.2, 0.4, 0.3);
      v /= Vector3d(4, 2, 2);
      return v == Vector3d(0.05, 0.2, 0.15);
    }, "Vector3/=(const DTU::Vector3&)");
    
    TestCase([](){
      Vector3d v(2, 3, 5);
      Vector3d w = v.normalised();
      return v == Vector3d(2, 3, 5) && w == Vector3d(0.2, 0.3, 0.5);
    }, "Vector3::normalised");
    
    TestCase([](){
      Vector3d v(2, 3, 5);
      v.normalise();
      return v == Vector3d(0.2, 0.3, 0.5);
    }, "Vector3::normalise");
    
    TestCase([](){
      Vector3d v(4, 8, 8);
      return v.magnitude() == 12;
    }, "Vector3::magnitude");
    
    TestCase([](){
      Vector3d v(4, 8, 8);
      return v.magnitudeSquared() == 144;
    }, "Vector3::magnitudeSquared");
    
    TestCase([](){
      Vector3d v(3, 4, 3);
      Vector3d w(2, -5, 2);
      return v.dot(w) == -8;
    }, "Vector3::dot(const Vector3<T>&)");
    
    TestCase([](){
      Vector3d v(3, 4, 3);
      Vector3d w(2, -5, 2);
      return Vector3d::dot(v, w) == -8;
    }, "Vector3::dot(const Vector3<T>&, const Vector3<T>&)");
    
    TestCase([](){
      Vector3d v(3, 3, 0);
      return APPROX_EQUALS(v.angle(Vector3d::right), PI / 4);
    }, "Vector3::angle(const Vector3<T>&)");
    
    TestCase([](){
      Vector3d v(0, 5, 5);
      return APPROX_EQUALS(Vector3d::angle(v, Vector3d::left), 3 * PI / 4);
    }, "Vector3::angle(const Vector3<T>&, const Vector3<T>&)");
  }
}