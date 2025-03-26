#include "raylib.h"
#include <coriolis/math/vector.hpp>
#include <coriolis/physics/particle.hpp>
#include <random>

Vector3 toRL(coriolis::Vector3 vec) {
    return Vector3 { (float)vec.x, (float)vec.y, (float)vec.z };
}

coriolis::Particle* randomParticle() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<real> dist(-25, 25);

    coriolis::Vector3 pos { 0.0, 5.0, 0.0 };
    coriolis::Vector3 vel { dist(gen), dist(gen), dist(gen) };
    coriolis::Vector3 acc { 0.0, dist(gen), 0.0 };

    coriolis::Particle* a = new coriolis::Particle(pos,vel,acc,0.9999,0.25);

    a->lifetime = 4;

    return a;
}

int main(void)
{
    std::vector<coriolis::Particle*> particles {};

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    Camera3D camera = {};
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 5.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float spawn_particle_every = 0.000001;

    float particle_time = spawn_particle_every;

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_FREE);

        float delta = GetFrameTime();

        particle_time -= delta;

        if (particle_time <= 0.0) {
            particles.push_back(randomParticle());
            particle_time = spawn_particle_every;
        }

        if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };

        BeginDrawing();

            ClearBackground(WHITE);

            BeginMode3D(camera);

            for (auto it = particles.begin(); it != particles.end(); ) {
                coriolis::Particle* particle = *it;

                particle->integrate(delta);

                if (particle->lifetime <= 0) {
                    delete particle;
                    it = particles.erase(it);
                }

                DrawSphere(toRL(particle->pos), 0.4, RED);
                ++it;
            }

            DrawGrid(25,10);

            EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;

}
