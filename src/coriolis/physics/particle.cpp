#include <coriolis/platform/platform.hpp>
#include <coriolis/physics/particle.hpp>
#include <assert.h>

using namespace coriolis;

void Particle::integrate(real duration) {
    // Don't integrate stuff with infinite mass
    if (invMass <= 0.0f) return;

    assert(duration > 0.0);

    // Eq. 2.7 p' = p + p(dot) * t
    pos += vel * duration;

    // TODO(David): Add a force accumulator and set this here rather than leaving it const
    Vector3 resultingAcc = acc;

    resultingAcc += forceAccum * invMass;

    // Integrate velocity forward
    vel += resultingAcc * duration;

    // Apply damping force
    vel *= real_pow(damping, duration);

    // Clear forces
    clearAccumulator();

    // Update particle lifetime
    lifetime -= duration;
}

void Particle::clearAccumulator() {
    forceAccum.clear();
}

void Particle::addForce(const Vector3& force) {
    forceAccum += force;
}

bool Particle::hasFiniteMass() {
    return invMass >= 0.0;
}

real Particle::getMass() {
    if (invMass == 0.0) {
        return REAL_MAX;
    } else {
        return ((real)1)/invMass;
    }
}
