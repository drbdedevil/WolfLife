#include "Sheep.h"

#include "raylib.h"
#include "rlgl.h"

#include "../Components/Collision.h"

Sheep::Sheep(int x, int y) : AIVehicle(x, y)
{
    m_collision.reset(new Collision(this, 2.f));

    maxSpeed = 2.5f;
    maxForce = 4.2f;
    // bShouldBound = true;
}

void Sheep::update(float DeltaSeconds)
{
    AIVehicle::update(DeltaSeconds);
}

void Sheep::draw()
{
    DrawLineEx(Vector2(position.x, position.y), Vector2(position.x + velocity.x * 5.f, position.y + velocity.y * 5.f), 2.f, WHITE);

    float angle = atan2f(velocity.y, velocity.x);

    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    DrawCircle(0, 0, size, WHITE);

    rlPopMatrix();
}

void Sheep::execute()
{
}
