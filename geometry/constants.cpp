#pragma once

#include <cmath>

template <class T>
struct real_constant;

template <>
struct real_constant<double> {
  using value_type = double;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1e-9; }
  static constexpr value_type pi() { return std::acos(-1.0); }
};

template <>
struct real_constant<long double> {
  using value_type = long double;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<__float128> {
  using value_type = __float128;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1e-10; }
  static constexpr value_type pi() { return std::acos(-1.0L); }
};

template <>
struct real_constant<int32_t> {
  using value_type = int32_t;
  static constexpr value_type infinity() { return 1e9; }
  static constexpr value_type epsilon() { return 1; }
};

template <>
struct real_constant<int64_t> {
  using value_type = int64_t;
  static constexpr value_type infinity() { return 1e18; }
  static constexpr value_type epsilon() { return 1; }
};

template <class T, class U>
bool leq(T x, U y) {
  return x - y < real_constant<T>::epsilon();
}
template <class T, class U>
bool geq(T x, U y) {
  return y - x < real_constant<T>::epsilon();
}
template <class T, class U>
bool equal(T x, U y) {
  return leq(x, y) && geq(x, y);
}

template <class T>
T to_radian(T deg) {
  return deg * real_constant<T>::pi() / 180;
}
template <class T>
T to_degree(T rad) {
  return rad / real_constant<T>::pi() * 180;
}

/**
 * @title Geometric Constants
 */