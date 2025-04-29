#include "Wolf.h"

#include "Sheep.h"
#include "raylib.h"
#include "rlgl.h"

#include "../Components/Collision.h"

Wolf::Wolf(int x, int y, int8_t health) : Vehicle(x, y)
{
    m_collision.reset(new Collision(this, 5.f));

	m_health = health;
}

void Wolf::update(float DeltaSeconds)
{
    Vehicle::update(DeltaSeconds);
}

void Wolf::draw()
{
    // DrawLineEx(Vector2(position.x, position.y), GetMousePosition(), 2.f, WHITE);

    float angle = atan2f(velocity.y, velocity.x);

    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    DrawTriangle(
        { size * 2, 0 },
        { -size * 2, -size },
        { -size * 2, size },
        GREEN
    );

    rlPopMatrix();
}

int8_t Wolf::getHealth() const
{
    return m_health;
}

void Wolf::eatSheep(Sheep* sheep)
{
    sheep->die();
}

void Wolf::setVisibility(bool Value)
{
    bIsVisible = Value;
}

bool Wolf::isVisible() const
{
    return bIsVisible;
}

void Wolf::tear()
{
    --m_health;
    if (m_health <= 0)
    {
        m_health = 0;
        bIsAlive = false;
    }
}
