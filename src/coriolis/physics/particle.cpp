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

    // Integrate velocity forward
    vel += resultingAcc * duration;

    // Apply damping force
    vel *= powf(damping, duration);

    // Clear forces
    clearAccumulator();

    // Update particle lifetime
    lifetime -= duration;
}

// TODO implement me
void Particle::clearAccumulator() {

}
