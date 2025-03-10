#include <coriolis/platform/platform.h>
#include <optional>

#ifndef CORIOLIS_MATH_VECTOR3_HPP
#define CORIOLIS_MATH_VECTOR3_HPP

namespace coriolis {

struct Basis3;

struct Vector3 {
  real x = 0.0;
  real y = 0.0;
  real z = 0.0;

  constexpr Vector3() = default;
  constexpr Vector3(real x, real y, real z) : x(x), y(y), z(z) {}

  // Computes the magnitude of the vector
  real mag() const noexcept;

  // Computes the square of the magnitude of the vector
  // More efficient if all you are doing is comparing the magnitude of the
  // vectors
  real sqr_mag() const noexcept;

  // normalizes vector in place
  void norm() noexcept;

  // Subtracts two vectors
  Vector3 subtract(const Vector3 &other) const noexcept;

  // Adds two vectors
  Vector3 add(const Vector3 &other) const noexcept;

  // Scale vector by real number
  Vector3 scale(const real &s) const noexcept;

  // Computes the vector product (elementwise multiplication), completely
  // useless
  Vector3 component_product(const Vector3 &other) const noexcept;

  // Computes the dot product (sometimes called the Scalar Product)
  // a . b = |a| |b| cos theta
  real dot_product(const Vector3 &other) const noexcept;

  // Computes the cross product (sometimes called the Vector Product)
  // a x b = |a| |b| sin theta
  Vector3 cross_product(const Vector3 &other) const noexcept;

  // Computes the angle in radians between two vectors
  // theta = cos-1(a . b / |a| |b|)
  real angle_between(const Vector3 &other) const noexcept;

  // Gives us a Basis from vector a and b, with a being retained as one of the
  // orthogonal axes
  static std::optional<Basis3> basis_from(Vector3 &a, Vector3 &b) noexcept;

  // Operator overloads
  constexpr Vector3 operator+(const Vector3& other) const noexcept {
      return add(other);
  }
  
  constexpr Vector3 operator-(const Vector3& other) const noexcept {
      return subtract(other);
  }
  
  constexpr Vector3 operator*(real scalar) const noexcept {
      return scale(scalar);
  }
  
  constexpr real operator^(const Vector3& other) const noexcept {
      return dot_product(other);
  }
  
  constexpr Vector3 operator%(const Vector3& other) const noexcept {
      return cross_product(other);
  }
  
  constexpr bool operator==(const Vector3 &other) const noexcept {
      return x==other.x && y==other.y && z==other.z;
  }
};

struct Basis3 {
  Vector3 i;
  Vector3 j;
  Vector3 k;

  constexpr Basis3(Vector3 i, Vector3 j, Vector3 k) : i(i), j(j), k(k) {}
};

} // namespace coriolis

#endif // CORIOLIS_MATH_VECTOR3_HP
