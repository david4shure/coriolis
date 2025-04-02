#include <coriolis/math/vector.hpp>

#include <cmath>
#include <optional>

using namespace coriolis;

real Vector3::sqr_mag() const noexcept {
    return x * x + y * y + z * z;
}

real Vector3::mag() const noexcept {
    return std::sqrt(x * x + y * y + z * z);
}

// normalizes vector in place
void Vector3::norm() noexcept {
    real magnitude = mag();
    x/=magnitude;
    y/=magnitude;
    z/=magnitude;
}

// Subtracts two vectors
Vector3 Vector3::subtract(const Vector3& other) const noexcept {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

// Adds two vectors
Vector3 Vector3::add(const Vector3& other) const noexcept {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

// Scale vector by real number
Vector3 Vector3::scale(const real& s) const noexcept {
    return Vector3(s * x, s * y, s * z);
}

// Computes the vector product (elementwise multiplication), completely useless
Vector3 Vector3::component_product(const Vector3& other) const noexcept {
    return Vector3(x * other.x, y * other.y, z * other.z);
}


// Computes the dot product (sometimes called the Scalar Product)
// a . b = |a| |b| cos theta
real Vector3::dot_product(const Vector3& other) const noexcept {
    return x*other.x + y*other.y + z*other.z;
}

// Computes the cross product (sometimes called the Vector Product)
// a x b = |a| |b| sin theta
Vector3 Vector3::cross_product(const Vector3& other) const noexcept {
    return Vector3(y*other.z-z*other.y,z*other.x - x*other.z,x*other.y-y*other.x);
}

// Computes the angle in radians between two vectors
// theta = cos-1(a . b / |a| |b|)
real Vector3::angle_between(const Vector3& other) const noexcept {
    real dot = dot_product(other);
    return acos(dot / (mag() * other.mag()));
}

void Vector3::clear() noexcept {
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

// Gives us a Basis from vector a and b, with a being retained as one of the
// orthogonal axes
std::optional<Basis3> Vector3::basis_from(Vector3& a, Vector3& b) noexcept {
    a.norm();
    Vector3 c = a % b;
    if (c.sqr_mag() == 0.0) return std::nullopt;
    c.norm();
    b = c % a;
    return Basis3 {a,b,c};
}
