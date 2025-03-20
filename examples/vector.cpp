#include "raylib.h"
#include <coriolis/math/vector.hpp>

int main(void)
{
    coriolis::Vector3 a = { 4, 3, 7 };
    coriolis::Vector3 b = { 5, 2, 1 };
    coriolis::Vector3 c = a + b;

    Vector3 a_r = {(float)a.x,(float)a.y,(float)a.z};
    Vector3 b_r = {(float)b.x,(float)b.y,(float)b.z};
    Vector3 c_r = {(float)c.x,(float)c.y,(float)c.z};
    Vector3 zero = {0,0,0};

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");


    Camera3D camera = {};
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };


        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);
                DrawLine3D(zero,a_r,BLUE);
                DrawLine3D(zero,b_r,GREEN);
                DrawLine3D(b_r,c_r,RED);
            EndMode3D();

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
