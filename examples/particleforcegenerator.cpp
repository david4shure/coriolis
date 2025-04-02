#include "raylib.h"
#include <coriolis/math/vector.hpp>
#include <coriolis/physics/firework.hpp>
#include <coriolis/math/random.hpp>
#include <coriolis/physics/pfreg.hpp>
#include "assert.h"
#include <memory>
#include <sstream>

constexpr static int MAX_PARTICLES = 80'000;

Vector3 toRL(coriolis::Vector3 vec) {
    return Vector3 { (float)vec.x, (float)vec.y, (float)vec.z };
}

int main(void)
{
    std::vector<std::unique_ptr<coriolis::FireworkRule>> rules = coriolis::FireworkRule::GetDefaultFireworkRules();
    std::vector<std::unique_ptr<coriolis::Firework>> fireworks {};
    std::unique_ptr<coriolis::ParticleForceRegistry> registry  = std::make_unique<coriolis::ParticleForceRegistry>();

    std::unique_ptr<coriolis::ParticleGravity> gravity = std::make_unique<coriolis::ParticleGravity>(coriolis::Vector3(0.0,-11.0,0.0));
    std::unique_ptr<coriolis::ParticleDrag> drag = std::make_unique<coriolis::ParticleDrag>(0.1,0.01);
    std::unique_ptr<coriolis::ParticleUplift> uplift = std::make_unique<coriolis::ParticleUplift>(coriolis::Vector3(0,0,0),10.0,10.0,20);
    std::unique_ptr<coriolis::ParticleGravityCenter> gravCenter = std::make_unique<coriolis::ParticleGravityCenter>(coriolis::Vector3(0.0,0.0,0.0));

    fireworks.resize(MAX_PARTICLES);

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    Camera3D camera = {};
    camera.position = { 16.0f, 115.0f, 135.0f };  // Move camera back and up
    camera.target = { 0.0f, 30.0f, 0.0f };     // Look at origin
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    DisableCursor();

    int firework_index = 0;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        float delta = GetFrameTime();
        fireworks.size();

        registry->updateForces(delta);

        // Process existing fireworks
        for (size_t i = 0; i < fireworks.size(); i++) {
            auto& firework = fireworks[i];

            if (firework == nullptr) {
                continue;
            }

            bool expired = firework->update(delta);

            if (expired) {
                // Process payloads and create new fireworks
                auto rule = coriolis::FireworkRule::RuleForType(rules, firework->type);
                if (rule->type == firework->type) {
                    coriolis::Vector3 pos = firework->particle->pos;
                    coriolis::Vector3 vel = firework->particle->vel;

                    for (const auto& payload : rule->payloads) {
                        auto rule_for_payload = coriolis::FireworkRule::RuleForType(rules, payload.type);

                        for (unsigned i = 0; i < payload.count; ++i) {

                            auto particle = std::make_unique<coriolis::Particle>(
                                pos,
                                vel + rule_for_payload->sampleVelocity(),
                                coriolis::Vector3(0, 0, 0),
                                rule_for_payload->damping,
                                1
                            );

                            if (fireworks[firework_index] != nullptr) {
                                registry->remove(fireworks[firework_index]->particle.get(), gravity.get());
                                registry->remove(fireworks[firework_index]->particle.get(), drag.get());
                                registry->remove(fireworks[firework_index]->particle.get(), uplift.get());
                            }

                            fireworks[firework_index] =
                                std::make_unique<coriolis::Firework>(
                                    std::move(particle),
                                    coriolis::randomReal(rule_for_payload->minAge, rule_for_payload->maxAge),
                                    rule_for_payload->type
                                );

                            firework_index = (++firework_index) % MAX_PARTICLES;
                        }
                    }
                }

                registry->remove(firework->particle.get(), gravity.get());
                registry->remove(firework->particle.get(), drag.get());
                registry->remove(firework->particle.get(), uplift.get());
                fireworks[i] = nullptr;
            }
        }

        if (IsKeyDown(KEY_ONE)) {
            auto rule = rules[0].get();
            auto particle = std::make_unique<coriolis::Particle>(
                coriolis::Vector3(0,0,0),
                rule->sampleVelocity(),
                coriolis::Vector3(0,-10,0),
                rule->damping,
                1
            );

            registry->add(particle.get(), gravity.get());
            registry->add(particle.get(), uplift.get());

            auto firework = std::make_unique<coriolis::Firework>(
                std::move(particle),
                coriolis::randomReal(rule->minAge, rule->maxAge),
                0
            );


            if (fireworks[firework_index] != nullptr) {
                registry->remove(fireworks[firework_index]->particle.get(), gravity.get());
                registry->remove(fireworks[firework_index]->particle.get(), drag.get());
                registry->remove(fireworks[firework_index]->particle.get(), uplift.get());
            }

            fireworks[firework_index] = std::move(firework);
            firework_index = (++firework_index) % MAX_PARTICLES;
        }

        if (IsKeyDown(KEY_TWO)) {
            auto rule = rules[7].get();
            auto particle = std::make_unique<coriolis::Particle>(
                coriolis::Vector3(0,0,0),
                rule->sampleVelocity(),
                coriolis::Vector3(0,-10,0),
                rule->damping,
                3
            );

            registry->add(particle.get(), drag.get());

            auto firework = std::make_unique<coriolis::Firework>(
                std::move(particle),
                coriolis::randomReal(rule->minAge, rule->maxAge),
                7
            );

            if (fireworks[firework_index] != nullptr) {
                registry->remove(fireworks[firework_index]->particle.get(), gravity.get());
                registry->remove(fireworks[firework_index]->particle.get(), drag.get());
                registry->remove(fireworks[firework_index]->particle.get(), uplift.get());
            }


            fireworks[firework_index] = std::move(firework);
            firework_index = (++firework_index) % MAX_PARTICLES;
        }

        if (IsKeyDown(KEY_THREE)) {
            auto rule = rules[8].get();
            auto particle = std::make_unique<coriolis::Particle>(
                coriolis::randomVector(coriolis::Vector3(30,0,0), coriolis::Vector3(30,0,0)),
                rule->sampleVelocity(),
                coriolis::Vector3(0,0,0),
                rule->damping,
                3
            );

            registry->add(particle.get(), gravCenter.get());

            auto firework = std::make_unique<coriolis::Firework>(
                std::move(particle),
                coriolis::randomReal(rule->minAge, rule->maxAge),
                8
            );

            if (fireworks[firework_index] != nullptr) {
                registry->remove(fireworks[firework_index]->particle.get(), gravity.get());
                registry->remove(fireworks[firework_index]->particle.get(), drag.get());
                registry->remove(fireworks[firework_index]->particle.get(), uplift.get());
            }

            fireworks[firework_index] = std::move(firework);
            firework_index = (++firework_index) % MAX_PARTICLES;
        }

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
                int total_fireworks = 0;
                for (auto &firework : fireworks) {
                    if (firework == nullptr) {
                        continue;
                    }
                    total_fireworks++;
                    Color color;
                    switch (firework->type) {
                        case 0:
                            color = RED;
                            break;
                        case 1:
                            color = GREEN;
                            break;
                        case 2:
                            color = PURPLE;
                            break;
                        case 3:
                            color = ORANGE;
                            break;
                        case 4:
                            color = PINK;
                            break;
                        case 5:
                            color = SKYBLUE;
                            break;
                        case 6:
                            color = YELLOW;
                            break;
                        default:
                            color = BLUE;
                    }

                    DrawCube(toRL(firework->particle->pos),0.2,0.2,0.2,color);
                    /* DrawCircle3D(toRL(firework->particle->pos), 0.2, Vector3(0,1,0), 2.3, color); */
                    /* DrawSphereEx(toRL(firework->particle->pos), 0.2, 3,3,color); */
                }
                DrawSphere(Vector3(0,0,0), 3.0, RED);
                DrawGrid(25.0,10.0);
            EndMode3D();

            std::stringstream ss;
            ss << "Max number of particles: " << fireworks.size();
            std::string result = ss.str();
            DrawText(result.c_str(), 0, 10, 15, BLUE);
            std::stringstream nss;
            nss << "Firework index: " << firework_index;
            std::string index = nss.str();
            DrawText(index.c_str(), 0, 30, 15, GREEN);
            std::stringstream xss;
            xss << "Total Fireworks: " << total_fireworks;
            std::string total = xss.str();
            DrawText(total.c_str(), 0, 50, 15, RED);
            total_fireworks = 0;

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
