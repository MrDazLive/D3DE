#include "Vector2.h"

namespace DTU {

  template <>
  bool Vector2<float>::operator == (const Vector2<float>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y);
  }

  template <>
  bool Vector2<double>::operator == (const Vector2<double>& o) const {
    return APPROX_EQUALS(x, o.x) && APPROX_EQUALS(y, o.y);
  }

  template <>
  Vector2<int>& Vector2<int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }

  template <>
  Vector2<unsigned int>& Vector2<unsigned int>::normalise() {
    throw std::domain_error("Integral vectors can not be normalised");
  }
}