#include <coriolis/math/vector.hpp>

#ifndef CORIOLIS_MATH_RANDOM_HPP
#define CORIOLIS_MATH_RANDOM_HPP

namespace coriolis {
    Vector3 randomVector(Vector3 min, Vector3 max);
    real randomReal(real min, real max);
    Vector3 randomInSphere(Vector3 center, real radius);
    Vector3 randomInHemiSphere(Vector3 center, real radius);
}; // namespace coriolis
#endif // CORIOLIS_MATH_RANDOM_HPP
