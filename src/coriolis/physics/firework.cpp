#include <coriolis/physics/firework.hpp>
#include <coriolis/platform/platform.hpp>
#include <coriolis/math/random.hpp>
#include <memory>
#include <vector>

using namespace coriolis;

bool Firework::update(real duration) {
    // Integrate particle
    particle->integrate(duration);

    // Decrement lifetime
    lifetime -= duration;

    // If lifetime > 0.0, firework lives, return false
    return is_expired();
}

bool Firework::is_expired() {
    return lifetime <= 0.0;
}

std::vector<std::unique_ptr<FireworkRule>> FireworkRule::GetDefaultFireworkRules() {

    // Initialize our vector
    std::vector<std::unique_ptr<FireworkRule>> rules {};

    // FIREWORK #1
    auto rule1 = std::make_unique<FireworkRule>(
        0,
        3.0,
        4.0,
        0.9999,
        coriolis::Vector3(-6,30,-6),
        coriolis::Vector3(6,40,6)
    );
    rule1->payloads = {
        { 1,   // Type
          100 }, // Count
        { 2,
          50 }
    };


    auto rule2 = std::make_unique<FireworkRule>(
        1,
        0.5,
        1.0,
        0.99,
        coriolis::Vector3(10,10,10),
        coriolis::Vector3(-10,-10,-10)
    );
    rule2->payloads = {
        {
            3,
            1,
        }
    };

    // Smaller explosion than first, faster 3 other particles
    auto rule3 = std::make_unique<FireworkRule>(
        2,
        1.0,
        2.0,
        0.999,
        coriolis::Vector3(5,2,5),
        coriolis::Vector3(-5,5,-5)
    );
    rule3->payloads = {
        { 3,  // Type
          3 } // Count
    };

    auto rule4 = std::make_unique<FireworkRule>(
        3,
        0.1,
        0.3,
        0.5,
        coriolis::Vector3(3,2,3),
        coriolis::Vector3(-3,-3,-3)
    );
    rule4->payloads = {};

    // FIREWORK #2
    auto rule5 = std::make_unique<FireworkRule>(
        4,
        5.0,
        6.0,
        0.99,
        coriolis::Vector3(-6,40,-6),
        coriolis::Vector3(6,60,6)
    );
    rule5->payloads = {
        { 5,   // Type
          300 }, // Count
    };

    auto rule6 = std::make_unique<FireworkRule>(
        5,
        2.0,
        3.0,
        0.999,
        10,
        FireworkEmissionStrategyLabel::HemiSphere
    );
    rule6->payloads = {
        {
            6,
            10,
        }
    };

    auto rule7 = std::make_unique<FireworkRule>(
        6,
        0.3,
        0.7,
        0.8,
        4,
        FireworkEmissionStrategyLabel::Sphere
    );
    rule7->payloads = {
    };


    rules.push_back(std::move(rule1));
    rules.push_back(std::move(rule2));
    rules.push_back(std::move(rule3));
    rules.push_back(std::move(rule4));
    rules.push_back(std::move(rule5));
    rules.push_back(std::move(rule6));
    rules.push_back(std::move(rule7));


    return rules;
}

FireworkRule* FireworkRule::RuleForType(std::vector<std::unique_ptr<FireworkRule>>& rules, unsigned type) {
    for (auto &rule : rules) {
        if (rule->type == type) {
            return rule.get();
        }
    }

    return nullptr;
}

Vector3 FireworkRule::sampleVelocity() {
    if (sampleStrategy.type == AABB) {
        return randomVector(sampleStrategy.aabb.minVel, sampleStrategy.aabb.maxVel);
    } else if (sampleStrategy.type == Sphere) {
        return randomInSphere(Vector3(0,0,0), sampleStrategy.sphere.radius);
    } else if (sampleStrategy.type == HemiSphere) {
        return randomInHemiSphere(Vector3(0,0,0), sampleStrategy.hemisphere.radius);
    }
    return Vector3(0,0,0);
}
