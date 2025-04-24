#include "Dog.h"

#include "raylib.h"
#include "rlgl.h"

#include "Wolf.h"
#include "../Components/Collision.h"

Dog::Dog(int x, int y) : AIVehicle(x, y)
{
    m_collision.reset(new Collision(this, 4.f));

    maxSpeed = 8.2f;
    maxForce = 0.3f;
}

void Dog::update(float DeltaSeconds)
{
    AIVehicle::update(DeltaSeconds);
}

void Dog::draw()
{
    float angle = atan2f(velocity.y, velocity.x);

    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    DrawRectangle(0.f, 0.f, size * 2.5f, size * 2.5f, GRAY);

    rlPopMatrix();
}

void Dog::eatWolf(Wolf* wolf)
{
    wolf->die();
}
