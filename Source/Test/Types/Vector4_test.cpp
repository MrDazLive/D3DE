#include "declerations.h"

#include <Types/Vector4.h>

using namespace DTU;

namespace Types_Test {
  void Vector4::Reset() {}

  void Vector4::Examine() {
    TestCase([](){
      Vector4d v;
      return v.x == 0.0 && v.y == 0.0 && v.z == 0.0 && v.w == 0.0;
    }, "Vector4()");
    
    TestCase([](){
      Vector4d v(1.3);
      return v.x == 1.3 && v.y == 1.3 && v.z == 1.3 && v.w == 1.3;
    }, "Vector4(const T&)");
    
    TestCase([](){
      Vector4d v(0.7, 0.2, 0.4, 0.1);
      return v.x == 0.7 && v.y == 0.2 && v.z == 0.4 && v.w == 0.1;
    }, "Vector4(const T&, const T&)");
    
    TestCase([](){
      Vector2d w(0.2, 0.3);
      Vector4d v(w);
      return v.x == 0.2 && v.y == 0.3 && v.z == 0.0 && v.w == 0.0;
    }, "Vector4(const DTU::Vector2&)");
    
    TestCase([](){
      Vector3d w(0.2, 0.3, 0.5);
      Vector4d v(w);
      return v.x == 0.2 && v.y == 0.3 && v.z == 0.5 && v.w == 0.0;
    }, "Vector4(const DTU::Vector2&)");
    
    TestCase([](){
      Vector4d w(0.2);
      Vector4d v(w);
      return v.x == 0.2 && v.y == 0.2 && v.z == 0.2 && v.w == 0.2;
    }, "Vector4(const DTU::Vector4&)");
    
    TestCase([](){
      double a[4] = { 0.2, 0.4, 0.5, 0.3 };
      Vector4d v((const double*)a);
      return v.x == 0.2 && v.y == 0.4 && v.z == 0.5 && v.w == 0.3;
    }, "Vector4(const T*)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.1, 0.4);
      return v[0] == 0.2 && v[1] == 0.4 && v[2] == 0.1 && v[3] == 0.4;
    }, "Vector4[]");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.1, 0.8);
      return v == Vector4d(0.2, 0.4, 0.1, 0.8);
    }, "Vector4==(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.7, 0.2, 0.2, 0.3);
      return v != Vector4d(0.3, 0.2, 0.2, 0.1);
    }, "Vector4!=(const DTU::Vector4&");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.4, 0.1);
      return v + Vector4d(0.2, 0.3, 0.1, -0.1) == Vector4d(0.4, 0.7, 0.5, 0.0);
    }, "Vector4+(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.4, 0.1);
      return v - Vector4d(0.1, 0.0, 0.3, -0.1) == Vector4d(0.1, 0.4, 0.1, 0.2);
    }, "Vector4-(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.2, 0.5);
      return v * 2 == Vector4d(0.4, 0.8, 0.4, 1.0);
    }, "Vector4*(const T&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.7, 1.0);
      return v / 2 == Vector4d(0.1, 0.2, 0.35, 0.5);
    }, "Vector4/(const T&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.1, 0.4);
      Vector4d w(2.0, 3.0, 1.0, 0.5);
      return (v * w) == Vector4d(0.4, 1.2, 0.1, 0.2);
    }, "Vector4*(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.3, 0.1);
      Vector4d w(4, 2, 2, 1);
      return (v / w) == Vector4d(0.05, 0.2, 0.15, 0.1);
    }, "Vector4/(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.2, 0.3);
      v = 0.1;
      return v == Vector4d(0.1, 0.1, 0.1, 0.1);
    }, "Vector4=(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.0, 0.3);
      v += Vector4d(0.2, 0.3, 0.1, 0.3);
      return v == Vector4d(0.4, 0.7, 0.1, 0.6);
    }, "Vector4+=(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.1, 0.4);
      v -= Vector4d(0.1, 0.0, 0.1, 0.8);
      return v == Vector4d(0.1, 0.4, 0.0, -0.4);
    }, "Vector4-=(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.0, 0.3);
      v *= 2;
      return v == Vector4d(0.4, 0.8, 0.0, 0.6);
    }, "Vector4*=(const T&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.8, 1.0);
      v /= 2;
      return v == Vector4d(0.1, 0.2, 0.4, 0.5);
    }, "Vector4/=(const T&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 1.0, 0.2);
      v *= Vector4d(2.0, 3.0, 5.0, 3.0);
      return v == Vector4d(0.4, 1.2, 5.0, 0.6);
    }, "Vector4*=(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(0.2, 0.4, 0.3, 1.0);
      v /= Vector4d(4, 2, 2, 5);
      return v == Vector4d(0.05, 0.2, 0.15, 0.2);
    }, "Vector4/=(const DTU::Vector4&)");
    
    TestCase([](){
      Vector4d v(4, 4, 4, 4);
      Vector4d w = v.normalised();
      return v == Vector4d(4, 4, 4, 4) && w == Vector4d(0.5, 0.5, 0.5, 0.5);
    }, "Vector4::normalised");
    
    TestCase([](){
      Vector4d v(0.3, 0, 0, 0.4);
      v.normalise();
      return v == Vector4d(0.6, 0.0, 0.0, 0.8);
    }, "Vector4::normalise");
    
    TestCase([](){
      Vector4d v(5);
      return v.magnitude() == 10;
    }, "Vector4::magnitude");
    
    TestCase([](){
      Vector4d v(2, 4, 1, 3);
      return v.magnitudeSquared() == 30;
    }, "Vector4::magnitudeSquared");
    
    TestCase([](){
      Vector4d v(3, 4, 3, 1);
      Vector4d w(2, -5, 2, -1);
      return v.dot(w) == -9;
    }, "Vector4::dot(const Vector4<T>&)");
    
    TestCase([](){
      Vector4d v(3, 4, 3, 1);
      Vector4d w(2, -5, 2, -1);
      return Vector4d::dot(v, w) == -9;
    }, "Vector4::dot(const Vector4<T>&, const Vector4<T>&)");
  }
}