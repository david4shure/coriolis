/*******************************************************************************************
*
*   raylib [core] example - Initialize 3d camera free
*
*   Example complexity rating: [★☆☆☆] 1/4
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <coriolis/math/vector.hpp>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
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

    // Define the camera to look into our 3d world
    Camera3D camera = {};
    camera.position = { 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawLine3D(zero,a_r,BLUE);
                DrawLine3D(zero,b_r,GREEN);
                DrawLine3D(b_r,c_r,RED);
            EndMode3D();

            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
