#include <coriolis/platform/platform.hpp>
#include <coriolis/physics/particle.hpp>
#include <coriolis/physics/pfgen.hpp>
#include <vector>

#ifndef CORIOLIS_PHYSICS_FORCEREGISTRY_HPP
#define CORIOLIS_PHYSICS_FORCEREGISTRY_HPP

namespace coriolis {

struct ParticleForceRegistration {
    Particle* particle;
    IParticleForceGenerator* forceGen;
};

class ParticleForceRegistry {
public:
    // Our internal registrations
    std::vector<std::unique_ptr<ParticleForceRegistration>> registrations {};

    // Removes particle from our registry, if it doesn't exist nothing happens
    void remove(Particle* particle, IParticleForceGenerator* generator);

    // Registers a particle and generator
    void add(Particle* particle, IParticleForceGenerator* generator);

    // Clears out internal registry
    void clear();

    // Updates forces of all particles in our registry by the rules of their
    // corresponding Force Generators
    void updateForces(real duration);

}; // class ForceRegistry

}; // namespace coriolis

#endif // CORIOLIS_PHYSICS_FORCEREGISTRY_HPP
