#include "raylib.h"
#include <coriolis/math/vector.hpp>
#include <coriolis/physics/firework.hpp>
#include <coriolis/math/random.hpp>
#include "assert.h"
#include <iostream>
#include <memory>


Vector3 toRL(coriolis::Vector3 vec) {
    return Vector3 { (float)vec.x, (float)vec.y, (float)vec.z };
}

int main(void)
{
    std::vector<std::unique_ptr<coriolis::FireworkRule>> rules = coriolis::FireworkRule::GetDefaultFireworkRules();
    std::vector<std::unique_ptr<coriolis::Firework>> fireworks {};

    fireworks.reserve(5);

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

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);


        float delta = GetFrameTime();

        // Add this flag to your Firework class
        // bool markedForDeletion = false;

        // Then in your main loop
        std::vector<std::unique_ptr<coriolis::Firework>> newFireworks;

        // Process existing fireworks
        for (auto& firework : fireworks) {
            bool expired = firework->update(delta);

            if (expired) {
                // Process payloads and create new fireworks
                auto rule = coriolis::FireworkRule::RuleForType(rules, firework->type);
                if (rule->type == firework->type) {
                    coriolis::Vector3 pos = firework->particle->pos;
                    coriolis::Vector3 vel = firework->particle->vel;

                    for (const auto& payload : rule->payloads) {
                        for (unsigned i = 0; i < payload.count; ++i) {
                            auto rule_for_payload = coriolis::FireworkRule::RuleForType(rules, payload.type);

                            auto particle = std::make_unique<coriolis::Particle>(
                                pos,
                                vel + randomVector(rule_for_payload->minVel, rule_for_payload->maxVel),
                                coriolis::Vector3(0, -10, 0),
                                rule_for_payload->damping,
                                1
                            );

                            newFireworks.push_back(
                                std::make_unique<coriolis::Firework>(
                                    std::move(particle),
                                    coriolis::randomReal(rule_for_payload->minAge, rule_for_payload->maxAge),
                                    rule_for_payload->type
                                )
                            );
                        }
                    }
                }

                // Mark for deletion, but don't delete yet
                firework->markedForDeletion = true;
            }
        }

        // Create a new clean vector without deleted fireworks
        std::vector<std::unique_ptr<coriolis::Firework>> cleanFireworks;
        cleanFireworks.reserve(fireworks.size() + newFireworks.size());

        // Move valid fireworks to the new vector
        for (auto& firework : fireworks) {
            if (firework && !firework->markedForDeletion) {
                cleanFireworks.push_back(std::move(firework));
            }
        }

        // Add new fireworks
        for (auto& newFirework : newFireworks) {
            cleanFireworks.push_back(std::move(newFirework));
        }

        // Replace the old vector
        fireworks = std::move(cleanFireworks);

        if (IsKeyDown(KEY_ONE)) {
            auto rule = rules[0].get();
            auto particle = std::make_unique<coriolis::Particle>(
                coriolis::Vector3(0,0,0),
                randomVector(rule->minVel, rule->maxVel),
                coriolis::Vector3(0,-10,0),
                rule->damping,
                1
            );

            auto firework = std::make_unique<coriolis::Firework>(
                std::move(particle),
                coriolis::randomReal(rule->minAge, rule->maxAge),
                0
            );

            fireworks.push_back(std::move(firework));
        }

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
                for (auto &firework : fireworks) {
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
                        default:
                            color = BLUE;
                    }

                    DrawPoint3D(toRL(firework->particle->pos),color);
                    /* DrawCircle3D(toRL(firework->particle->pos), 0.2, Vector3(0,1,0), 2.3, color); */
                    /* DrawSphereEx(toRL(firework->particle->pos), 0.2, 3,3,color); */
                }
                DrawGrid(25.0,10.0);
            EndMode3D();

            std::string result = std::format("Number of particles {}", fireworks.size()); // "The answer is 42"
            DrawText(result.c_str(),0,10,15,BLUE);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
