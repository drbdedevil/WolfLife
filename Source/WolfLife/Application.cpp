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

    World* world = new World(2, 1);

    // Vehicle* mainHero = new Vehicle(50, 50);
    // Vehicle* lamb = new Vehicle(250, 250);
    // lamb->maxSpeed = 2.f;
    // lamb->maxForce = 0.2f;
    // lamb->bShouldBound = true;

    // Vehicle* veh3 = new Vehicle(550, 550);
    // veh3->maxSpeed = 380.f;
    // veh3->maxForce = 1200.f;

    while (!WindowShouldClose())
    {
        world->doForce();
        world->update(GetFrameTime());

        BeginDrawing();
        world->draw();

        // handle input
        Vector2 mousePos = GetMousePosition();
        DrawCircle(mousePos.x, mousePos.y, 10, RED);
        
        EndDrawing();
        // update
        // veh->seek(mousePos);
        // mainHero->arrive(mousePos);
        // mainHero->update(GetFrameTime());

        // if (lamb->position.x < lamb->bounds.x && (lamb->position.x > 1280 - lamb->bounds.x) && lamb->position.y < lamb->bounds.y && (lamb->position.y > 720 - lamb->bounds.y))
        // {
            // lamb->fleeing({ world->getWolf()->position.x, world->getWolf()->position.y});
        // }
        // else
        // {
            // lamb->boundaries();
        // }
        // lamb->update(GetFrameTime());

        // veh3->arrive({ mainHero->position.x, mainHero->position.y });
        // veh3->seek({ mainHero->position.x, mainHero->position.y });
        // veh3->update(GetFrameTime());

        // draw
        // mainHero->draw();
        // lamb->draw();
        // veh3->draw();
    }

    // delete mainHero;
    // delete lamb;
    // delete veh3;
    CloseWindow();
}