#pragma once

#include <cmath>
#include <cfloat>
#include <stdexcept>

#define PI 3.14159265359

#define MATH_TYPES(T)             \
  typedef T<int>           T##i;  \
  typedef T<unsigned int>  T##u;  \
  typedef T<float>         T##f;  \
  typedef T<double>        T##d;  \
  

#define APPROX_EQUALS(A, B)                     \
  std::abs(A - B) <= std::abs(A) * FLT_EPSILON  \

