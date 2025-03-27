#include <cmath>
#include <coriolis/math/random.hpp>
#include <coriolis/math/vector.hpp>
#include <random>

coriolis::Vector3 coriolis::randomVector(Vector3 min, Vector3 max) {
    real x = randomReal(min.x,max.x);
    real y = randomReal(min.y,max.y);
    real z = randomReal(min.z,max.z);

    return Vector3(x,y,z);
}

coriolis::Vector3 coriolis::randomInSphere(Vector3 center = Vector3(0,0,0), real radius = 1.0) {
    // Generate theta, phi, randomly
    real theta = randomReal(0, M_PI);
    real phi = randomReal(0, M_PI * 2);

    real x = radius*sin(theta)*cos(phi);
    real y = radius*sin(phi);
    real z = radius*cos(theta)*cos(phi);

    return Vector3(center.x+x,center.y+y,center.z+z);
}

coriolis::Vector3 coriolis::randomInHemiSphere(Vector3 center = Vector3(0,0,0), real radius = 1.0) {
    real x;
    real y;
    real z;

    do {
        // Generate theta, phi, randomly
        real theta = randomReal(0, M_PI);
        real phi = randomReal(0, M_PI * 2);

        x = radius*sin(theta)*cos(phi);
        y = radius*sin(phi);
        z = radius*cos(theta)*cos(phi);

    } while (y < 0);

    return Vector3(center.x+x,center.y+y,center.z+z);
}

real coriolis::randomReal(real min, real max) {
    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<real> dist(min, max);
    real result = dist(rng);
    return result;
}
