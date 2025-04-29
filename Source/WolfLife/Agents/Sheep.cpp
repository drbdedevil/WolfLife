#include "Sheep.h"

#include "raylib.h"
#include "rlgl.h"

#include "Wolf.h"
#include "../Components/Eyeshot.h"
#include "../Components/Collision.h"

Sheep::Sheep(int x, int y) : AIVehicle(x, y)
{
    m_startPos = Vector2(x, y);

    m_collision.reset(new Collision(this, 2.f));
    m_eyeshot.reset(new Eyeshot(this, 50.f, 10.f, 100.f));

    velocity = Vector2f(randomFloat(-1, 1), randomFloat(-1, 1));

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

    m_eyeshot->draw();

    DrawCircle(0, 0, size, GRAY);

    rlPopMatrix();
}

void Sheep::execute()
{
    if (m_sheepBehavior == ESB_Pasture)
    {
        bound();
    }
    else if (m_sheepBehavior == ESB_ReturnToPasture)
    {
        arrive({ m_startPos.x, m_startPos.y });

        if (CheckCollisionPointCircle({ position.x, position.y }, m_startPos, 20.f))
        {
            sheepShouldPasture();
        }
    }
    else if (m_sheepBehavior == ESB_RunningAway)
    {
        fleeingBoundIntelligent({ m_wolf->position.x, m_wolf->position.y });
    }
}

void Sheep::setWolf(std::shared_ptr<Wolf>& wolf)
{
    m_wolf = wolf.get();
}

void Sheep::setSheepBehavior(ESheepBehavior newBehavior)
{
    m_sheepBehavior = newBehavior;
}

void Sheep::sheepShouldPasture()
{
    m_sheepBehavior = ESB_Pasture;
}

void Sheep::sheepShouldReturnToPasture()
{
    m_sheepBehavior = ESB_ReturnToPasture;

    maxSpeed = 2.2f;
    maxForce = 2.2f;
}

void Sheep::sheepShouldRunningAway()
{
    m_sheepBehavior = ESB_RunningAway;

    maxSpeed = 2.5f;
    maxForce = 4.2f;
}
