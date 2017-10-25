#include "Vector4.h"

namespace DTU {

  template <>
  bool Vector4<float>::operator == (const Vector4<float>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y) && APPROX_EQUALS(z, o.z);
  }

  template <>
  bool Vector4<double>::operator == (const Vector4<double>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y) && APPROX_EQUALS(z, o.z);
  }

  template <>
  Vector4<int>& Vector4<int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }

  template <>
  Vector4<unsigned int>& Vector4<unsigned int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }
}