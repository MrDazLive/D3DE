#include "Vector3.h"

namespace DTU {

  template <>
  bool Vector3<float>::operator == (const Vector3<float>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y) && APPROX_EQUALS(z, o.z);
  }

  template <>
  bool Vector3<double>::operator == (const Vector3<double>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y) && APPROX_EQUALS(z, o.z);
  }

  template <>
  Vector3<int>& Vector3<int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }

  template <>
  Vector3<unsigned int>& Vector3<unsigned int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }
}