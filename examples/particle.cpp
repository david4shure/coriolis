#include "raylib.h"
#include <coriolis/math/vector.hpp>
#include <coriolis/physics/particle.hpp>
#include <random>

Vector3 toRL(coriolis::Vector3 vec) {
    return Vector3 { (float)vec.x, (float)vec.y, (float)vec.z };
}

coriolis::Particle* randomParticle() {
    std::random_device rd;  // Non-deterministic random seed
    std::mt19937 gen(rd());

    std::uniform_real_distribution<real> dist(-25, 25); // Uniform distribution [1, 100]
    
    coriolis::Vector3 pos { 0.0, 5.0, 0.0 };
    coriolis::Vector3 vel { dist(gen), dist(gen), dist(gen) };
    coriolis::Vector3 acc { 0.0, dist(gen), 0.0 };
    
    coriolis::Particle* a = new coriolis::Particle(pos,vel,acc,0.9999,0.25);

    a->lifetime = 4; // seconds

    return a;
}

int main(void)
{
    std::vector<coriolis::Particle*> particles {};

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");


    // Define the camera to look into our 3d world
    Camera3D camera = {};
    camera.position = { 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = { 0.0f, 5.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    float spawn_particle_every = 0.01; // seconds

    float particle_time = spawn_particle_every;

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);

        float delta = GetFrameTime();

        particle_time -= delta;

        if (particle_time <= 0.0) {
            particles.push_back(randomParticle());
            particle_time = spawn_particle_every;
        }

        if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

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
                
            EndMode3D();

            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;

    }
