#include "declerations.h"

#include <Types/Vector4.h>

#include <iostream>

using namespace DTU;

namespace Types_Test {
  void Vector2::Reset() {}

  void Vector2::Examine() {
    TestCase([](){
      Vector2d v;
      return v.x == 0.0 && v.y == 0.0;
    }, "Vector2()");
    
    TestCase([](){
      Vector2d v(1.3);
      return v.x == 1.3 && v.y == 1.3;
    }, "Vector2(const T&)");
    
    TestCase([](){
      Vector2d v(0.7, 0.2);
      return v.x == 0.7 && v.y == 0.2;
    }, "Vector2(const T&, const T&)");
    
    TestCase([](){
      Vector2d w(0.2);
      Vector2d v(w);
      return v.x == 0.2 && v.y == 0.2;
    }, "Vector2(const DTU::Vector2&)");
    
    TestCase([](){
      Vector3d w(0.2, 0.1, 0.5);
      Vector2d v(w);
      return v.x == 0.2 && v.y == 0.1;
    }, "Vector2(const DTU::Vector3&)");
    
    TestCase([](){
      Vector4d w(0.2, 0.3, 0.5, 0.8);
      Vector2d v(w);
      return v.x == 0.2 && v.y == 0.3;
    }, "Vector2(const DTU::Vector4&)");
    
    TestCase([](){
      double a[2] = { 0.2, 0.4 };
      Vector2d v((const double*)a);
      return v.x == 0.2 && v.y == 0.4;
    }, "Vector2(const T*)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      return v[0] == 0.2 && v[1] == 0.4;
    }, "Vector2[]");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      return v == Vector2d(0.2, 0.4);
    }, "Vector2==(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.7, 0.2);
      return v != Vector2d(0.3, 0.2);
    }, "Vector2!=(const DTU::Vector2&");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      return v + Vector2d(0.2, 0.3) == Vector2d(0.4, 0.7);
    }, "Vector2+(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      return v - Vector2d(0.1, 0.0) == Vector2d(0.1, 0.4);
    }, "Vector2-(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      return v * 2 == Vector2d(0.4, 0.8);
    }, "Vector2*(const T&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      return v / 2 == Vector2d(0.1, 0.2);
    }, "Vector2/(const T&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      Vector2d w(2.0, 3.0);
      return (v * w) == Vector2d(0.4, 1.2);
    }, "Vector2*(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      Vector2d w(4, 2);
      return (v / w) == Vector2d(0.05, 0.2);
    }, "Vector2/(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      v = 0.1;
      return v == Vector2d(0.1, 0.1);
    }, "Vector2=(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      v += Vector2d(0.2, 0.3);
      return v == Vector2d(0.4, 0.7);
    }, "Vector2+=(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      v -= Vector2d(0.1, 0.0);
      return v == Vector2d(0.1, 0.4);
    }, "Vector2-=(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      v *= 2;
      return v == Vector2d(0.4, 0.8);
    }, "Vector2*=(const T&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      v /= 2;
      return v == Vector2d(0.1, 0.2);
    }, "Vector2/=(const T&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      v *= Vector2d(2.0, 3.0);
      return v == Vector2d(0.4, 1.2);
    }, "Vector2*=(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(0.2, 0.4);
      v /= Vector2d(4, 2);
      return v == Vector2d(0.05, 0.2);
    }, "Vector2/=(const DTU::Vector2&)");
    
    TestCase([](){
      Vector2d v(4, 3);
      Vector2d w = v.normalised();
      return v == Vector2d(4, 3) && w == Vector2d(0.8, 0.6);
    }, "Vector2::normalised");
    
    TestCase([](){
      Vector2d v(4, 3);
      v.normalise();
      return v == Vector2d(0.8, 0.6);
    }, "Vector2::normalise");
    
    TestCase([](){
      Vector2d v(3, 4);
      return v.magnitude() == 5;
    }, "Vector2::magnitude");
    
    TestCase([](){
      Vector2d v(3, 4);
      return v.magnitudeSquared() == 25;
    }, "Vector2::magnitudeSquared");
    
    TestCase([](){
      Vector2d v(3, 4);
      Vector2d w(2, -5);
      return v.dot(w) == -14;
    }, "Vector2::dot(const Vector2<T>&)");
    
    TestCase([](){
      Vector2d v(3, 4);
      Vector2d w(2, -5);
      return Vector2d::dot(v, w) == -14;
    }, "Vector2::dot(const Vector2<T>&, const Vector2<T>&)");
    
    TestCase([](){
      Vector2d v(3, 3);
      return APPROX_EQUALS(v.angle(Vector2d::right), PI / 4);
    }, "Vector2::angle(const Vector2<T>&)");
    
    TestCase([](){
      Vector2d v(5, 5);
      return APPROX_EQUALS(Vector2d::angle(v, Vector2d::left), 3 * PI / 4);
    }, "Vector2::angle(const Vector2<T>&, const Vector2<T>&)");
  }
}