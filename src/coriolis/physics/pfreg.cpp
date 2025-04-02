#include <coriolis/physics/pfgen.hpp>
#include <coriolis/physics/pfreg.hpp>
#include <memory>

using namespace coriolis;

void ParticleForceRegistry::updateForces(real duration) {
    for (auto i = registrations.begin(); i < registrations.end(); i++) {
        auto fr = i->get();

        fr->forceGen->updateForce(fr->particle,duration);
    }
}

void ParticleForceRegistry::add(Particle* particle, IParticleForceGenerator* generator) {
    registrations.push_back(std::make_unique<ParticleForceRegistration>(
    ParticleForceRegistration{particle, generator}));
}

void ParticleForceRegistry::remove(Particle* particle, IParticleForceGenerator* generator) {
    auto it = std::find_if(registrations.begin(), registrations.end(), [&](const auto& reg) {
        return reg->particle == particle && reg->forceGen == generator;
    });

    if (it != registrations.end()) {
        registrations.erase(it);
    }
}

void ParticleForceRegistry::clear() {
    registrations.clear();
}
