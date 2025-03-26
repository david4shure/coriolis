#include <coriolis/physics/firework.hpp>
#include <coriolis/platform/platform.hpp>
#include <memory>
#include <vector>

using namespace coriolis;

bool Firework::update(real duration) {
    // Integrate particle
    particle->integrate(duration);

    // Decrement lifetime
    lifetime -= duration;

    // If lifetime > 0.0, firework lives, return false
    return lifetime <= 0.0;
}

std::vector<std::unique_ptr<FireworkRule>> FireworkRule::GetDefaultFireworkRules() {

    // Initialize our vector
    std::vector<std::unique_ptr<FireworkRule>> rules {};

    // Explodes, falls very slowly down down down
    auto rule1 = std::make_unique<FireworkRule>(
        0,
        3.0,
        4.0,
        0.9999,
        coriolis::Vector3(-3,30,-3),
        coriolis::Vector3(3,40,3)
    );
    rule1->payloads = {
        { 1,   // Type
          90 }, // Count
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

    rules.push_back(std::move(rule1));
    rules.push_back(std::move(rule2));
    rules.push_back(std::move(rule3));
    rules.push_back(std::move(rule4));


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
