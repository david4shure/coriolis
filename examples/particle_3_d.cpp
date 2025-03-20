#include "raylib.h"
#include <coriolis/math/vector.hpp>
#include <coriolis/physics/particle.hpp>
#include <random>
#include <chrono>
#include <thread>
#include <stdio.h>

Vector3 toRL(coriolis::Vector3 vec) {
    return Vector3 { (float)vec.x, (float)vec.y, (float)vec.z };
}

void integrate_35(coriolis::Particle* particle,real duration) {
    // Don't integrate stuff with infinite mass
    if (particle->invMass <= 0.0f) return;

    // Eq. 2.7 p' = p + p(dot) * t
    particle->pos += particle->vel * duration;

    // TODO(David): Add a force accumulator and set this here rather than leaving it const
    coriolis::Vector3 resultingAcc = particle->acc;

    // Integrate velocity forward
    particle->vel += resultingAcc * duration;

    // Apply damping force
    particle->vel *= (particle->damping);

    // Clear forces
    particle->clearAccumulator();

    // Update particle lifetime
    particle->lifetime -= duration;
}

coriolis::Particle* getParticle(real x) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<real> dist(-25, 25);

    coriolis::Vector3 pos { x, 20.0, 0.0 };
    coriolis::Vector3 vel { 0, 0.0, 0.0 };
    coriolis::Vector3 acc { 0.0, -1.0, 0.0 };

    coriolis::Particle* a = new coriolis::Particle(pos,vel,acc,0.9999,0.25);

    a->lifetime = 4;

    return a;
}

int main(void)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    std::vector<coriolis::Particle*> particles {};
    coriolis::Particle* a = getParticle(-3);
    coriolis::Particle* b = getParticle(3);

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    Camera3D camera = {};
    camera.position = { 0.0f, 0.0f, 30.0f };
    camera.target = { 0.0f, 5.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float spawn_particle_every = 0.01;

    float particle_time = spawn_particle_every;

    DisableCursor();

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        #include <thread>

        int sleep_time = dist(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

        UpdateCamera(&camera, CAMERA_FREE);

        float delta = GetFrameTime();

        particle_time -= delta;

        if (particle_time <= 0.0) {
            /* particles.push_back(randomParticle()); */
            particle_time = spawn_particle_every;
        }

        if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };


        BeginDrawing();

            ClearBackground(BLACK);
            std::string message = std::format("Ball A height {}", truncf(a->pos.y));
            DrawText(message.c_str(), 100, 50, 10, RED);

            message = std::format("Ball B height {}", truncf(b->pos.y));
            DrawText(message.c_str(), 550, 50, 10, BLUE);

            std::string higher_ball = "a";

            if (b->vel.sqr_mag() < a->vel.sqr_mag()) {
                higher_ball = "b";
            }

            message = std::format("{} is going faster", higher_ball);
            DrawText(message.c_str(), 260, 50, 10, higher_ball == "b" ? BLUE : RED);

            BeginMode3D(camera);

            if (delta != 0.0) {
                a->integrate(delta);
                integrate_35(b,delta);
            }

            DrawSphere(toRL(a->pos), 0.4, RED);
            DrawSphere(toRL(b->pos), 0.4, BLUE);
            EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;

    }
