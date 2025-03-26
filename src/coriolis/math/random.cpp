#include <coriolis/math/random.hpp>
#include <coriolis/math/vector.hpp>
#include <random>

coriolis::Vector3 coriolis::randomVector(Vector3 min, Vector3 max) {
    real x = randomReal(min.x,max.x);
    real y = randomReal(min.y,max.y);
    real z = randomReal(min.z,max.z);

    return Vector3(x,y,z);
}

real coriolis::randomReal(real min, real max) {
    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<real> dist(min, max);
    real result = dist(rng);
    return result;
}
