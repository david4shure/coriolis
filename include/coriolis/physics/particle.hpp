#include <coriolis/math/vector.hpp>

#ifndef CORIOLIS_PHYSICS_PARTICLE_HPP
#define CORIOLIS_PHYSICS_PARTICLE_HPP

namespace coriolis {

class Particle {
public:
    constexpr Particle(Vector3 pos, Vector3 vel, Vector3 acc, real damping, real invMass) : pos(pos), vel(vel), acc(acc), damping(damping), invMass(invMass) {}

    real lifetime;

    // Particle Physics State
    // Holds the position of particle
    Vector3 pos;

    // Linear velocity of particle
    Vector3 vel;

    // Acceleration of particle
    Vector3 acc;

    // Internal parameters
    // Damping prevents the numerical integration inaccuracies,
    //  removes energy added by numerical instabilities.
    real damping;

    // Inverse mass of the particle
    // We store it this way to simulate zero mass objects
    // without causing divided my zero errors, ie, a = F/m will explode
    real invMass;

    // Integrates the particle forward in time by the set amount
    // Newton-Euler method
    void integrate(real duration);

    // Accumumlated force, many different forces will be added to this
    // single vector
    Vector3 forceAccum;

    // Clears force accumulator
    void clearAccumulator();

    // Adds force to forceAccum
    void addForce(const Vector3& force);

    // Returns true if particle has positive mass
    bool hasFiniteMass();

    // gets the actual mass
    // (Does a computation to turn invMass into mass)
    real getMass();
}; // struct Particle

}; // namespace coriolis
#endif // CORIOLIS_PHYSICS_PARTICLE_HPP
