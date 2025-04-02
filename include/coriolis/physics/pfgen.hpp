#include <coriolis/platform/platform.hpp>
#include <coriolis/physics/particle.hpp>

#ifndef CORIOLIS_PHYSICS_FORCEGEN_HPP
#define CORIOLIS_PHYSICS_FORCEGEN_HPP

namespace coriolis {
class IParticleForceGenerator {
public:
    virtual void updateForce(coriolis::Particle* particle, const real duration) = 0;
    virtual ~IParticleForceGenerator() = default;
protected:
    IParticleForceGenerator() = default;
}; // iparticle force generator

// Basic particle gravity implemented
class ParticleGravity : public IParticleForceGenerator {
    Vector3 gravity;

public:
    inline ParticleGravity(const Vector3 gravity): gravity(gravity) {};

    void updateForce(Particle* particle, const real duration) override;
    ~ParticleGravity();
}; // particle gravity

class ParticleDrag : public IParticleForceGenerator {
    real k1;
    real k2;

public:
    inline ParticleDrag(const real k1, const real k2) : k1(k1), k2(k2) {};

    void updateForce(Particle* particle, real duration) override;
    ~ParticleDrag();
};

class ParticleUplift : public IParticleForceGenerator {
    const Vector3 center;
    const real x_threshold;
    const real z_threshold;
    const real upward_force_value;

public:
    inline ParticleUplift(const Vector3 center, const real x_threshold, const real z_threshold, const real upward_force_value) : center(center), x_threshold(x_threshold), z_threshold(z_threshold), upward_force_value(upward_force_value) {};

    void updateForce(Particle* particle, real duration) override;
    ~ParticleUplift();
};

class ParticleGravityCenter : public IParticleForceGenerator {
    const Vector3 gravCenter;

public:
    inline ParticleGravityCenter(const Vector3 gravCenter) : gravCenter(gravCenter) {};

    void updateForce(Particle* particle, real duration) override;
    ~ParticleGravityCenter();
};

} // namespace

#endif // CORIOLIS_PHYSICS_FORCEGEN_HPP
