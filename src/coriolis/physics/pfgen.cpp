#include <coriolis/platform/platform.hpp>
#include <coriolis/physics/pfgen.hpp>

#include "stdio.h"

using namespace coriolis;

ParticleGravity::~ParticleGravity() = default;
ParticleDrag::~ParticleDrag() = default;
ParticleUplift::~ParticleUplift() = default;
ParticleGravityCenter::~ParticleGravityCenter() = default;

void ParticleGravity::updateForce(Particle* particle, real duration) {
    if (!particle->hasFiniteMass()) return;

    particle->addForce(gravity * particle->getMass());
}

void ParticleDrag::updateForce(Particle* particle, real duration) {
    Vector3 force = particle->vel;

    real dragCoef = force.mag();
    dragCoef = k1 * dragCoef + k2 * dragCoef * dragCoef;

    force.norm();

    force *= -dragCoef;

    particle->addForce(force);
}

void ParticleUplift::updateForce(Particle* particle, real duration) {
    real z_diff = real_abs(particle->pos.z - center.z);
    real x_diff = real_abs(particle->pos.x - center.x);

    if (x_diff > x_threshold) {
        return;
    }

    if (z_diff > z_threshold) {
        return;
    }

    particle->addForce(Vector3(0,upward_force_value,0));
}

void ParticleGravityCenter::updateForce(Particle* particle, real duration) {
    Vector3 particleToCenter = particle->pos - gravCenter; 
    particleToCenter.norm();
    particleToCenter.scale(1.0/particleToCenter.sqr_mag());

    particle->addForce(particleToCenter*-10);
}
