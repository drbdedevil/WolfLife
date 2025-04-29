#include "Application.h"

#include "World.h"
#include "Agents/Vehicle.h"
#include "Agents/Wolf.h"
#include "raylib.h"

Application::Application()
{

}

Application::~Application()
{

}

void Application::run()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "WolfLife");
    SetTargetFPS(60);

    World* world = new World(200, 2);

    while (!WindowShouldClose())
    {
        world->doForce();
        world->update(GetFrameTime());

        BeginDrawing();
        world->draw();

        // handle input
        // Vector2 mousePos = GetMousePosition();
        // DrawCircle(mousePos.x, mousePos.y, 10, RED);
        
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}