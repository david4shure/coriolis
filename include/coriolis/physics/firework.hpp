#include <coriolis/physics/particle.hpp>
#include <coriolis/platform/platform.hpp>
#include <vector>

#ifndef CORIOLIS_PHYSICS_FIREWORK_HPP
#define CORIOLIS_PHYSICS_FIREWORK_HPP

namespace coriolis {

struct FireworkPayload {
    // Type of firework to emit
    unsigned type;

    // The number of fireworks to emit
    unsigned count;
};

class Firework {
public:
    // Constructor
    Firework(std::unique_ptr<Particle> particle, real lifetime, unsigned type) : particle(std::move(particle)), lifetime(lifetime), type(type) {}

    // The internal particle (pos,vel,acc) of the current firework
    std::unique_ptr<Particle> particle;

    // The lifetime of the firework, the amount of seconds
    // before the firework stages.
    real lifetime;

    // What type of firework is it, corresponds to type of FireworkRule
    unsigned type;

    bool markedForDeletion;

    // Update function
    bool update(real duration);

}; // class Particle


struct FireworkRule {
    // Type of firework
    const unsigned type;

    // Minimum of the age of the firework
    real minAge;

    // Maximum of the age of the firework
    real maxAge;

    // Damping factor on velocity
    real damping;

    // Minimum velocity of the firework
    coriolis::Vector3 minVel;

    // Maximum velocity of the firework
    coriolis::Vector3 maxVel;

    std::vector<FireworkPayload> payloads;

    // Static method to grab the firework rules
    static std::vector<std::unique_ptr<FireworkRule>> GetDefaultFireworkRules();

    static FireworkRule* RuleForType(std::vector<std::unique_ptr<FireworkRule>>& rules, unsigned type);

    // Constructor
    constexpr FireworkRule(
            const unsigned type,
            real minAge,
            real maxAge,
            real damping,
            coriolis::Vector3 minVel,
            coriolis::Vector3 maxVel)
        :
            type(type), minAge(minAge), maxAge(maxAge), damping(damping), minVel(minVel), maxVel(maxVel) {};
};

} // namespace coriolis

#endif // CORIOLIS_PHYSICS_FIREWORK_HPP
