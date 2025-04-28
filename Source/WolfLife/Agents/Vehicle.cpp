#include "Vehicle.h"

#include <algorithm>
#include "rlgl.h"

#include "../Components/Collision.h"
#include <iostream>

Vehicle::Vehicle(int x, int y)
{
    m_collision.reset();

    position = Vector2f(x, y);
	velocity = Vector2f(0, 0);
	acceleration = Vector2f(0, 0);

    bounds = Vector2(1066, 600);

	size = 6.f;
	maxSpeed = 8.f;
	maxForce = 0.3f;
}

void Vehicle::update(float DeltaSeconds)
{
    // acceleration = acceleration * DeltaSeconds;

    velocity = velocity + acceleration;

    const float velLength = velocity.Length();
    if (velLength > maxSpeed)
    {
        velocity = velocity.Normalized() * maxSpeed;
    }

    position.x += velocity.x;
    position.y += velocity.y;

    acceleration = { 0.0f, 0.0f };
}

void Vehicle::applyForce(const Vector2& force)
{
	acceleration = Vector2f(acceleration.x + force.x, acceleration.y + force.y);
}

void Vehicle::draw()
{
    float angle = atan2f(velocity.y, velocity.x);

    // Рисуем треугольник вручную
    // BeginMode2D({ 0 }); // простой режим без камеры, но можно использовать для push/pop матриц

    // Применяем трансформации: перевод и поворот
    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    // Рисуем треугольник
    DrawTriangle(
        { size * 2, 0 },
        { -size * 2, -size },
        { -size * 2, size },
        GREEN
    );

    rlPopMatrix();
    // EndMode2D();
}

void Vehicle::seek(const Vector2& target)
{
    Vector2f desired = { target.x - position.x, target.y - position.y };

    desired = desired.Normalized() * maxSpeed;

    Vector2f steer = { desired.x - velocity.x, desired.y - velocity.y };

    if (steer.Length() > maxForce) 
    {
        steer = steer.Normalized() * maxForce;
    }

    applyForce({steer.x, steer.y });
}

void Vehicle::fleeing(const Vector2& target)
{
    Vector2f desired = { position.x - target.x, position.y - target.y };

    desired = desired.Normalized() * maxSpeed;

    Vector2f steer = { desired.x - velocity.x, desired.y - velocity.y };

    if (steer.Length() > maxForce)
    {
        steer = steer.Normalized() * maxForce;
    }

    applyForce({ steer.x, steer.y });
}

void Vehicle::arrive(const Vector2& target)
{
    const Vector2f targetF = Vector2f(target.x, target.y);
    Vector2f desired = targetF - position;
    float distance = desired.Length();

    float speed = maxSpeed;
    if (distance < 150.0f)
    {
        // speed = (distance / 3000.0f) * maxSpeed;
        speed = map(distance, 0, 150.f, 0, maxSpeed);
        // std::cout << "Distance: " << distance << " Speed: " << speed << std::endl;
    }

    desired = desired.Normalized() * speed;

    Vector2f steer = desired - velocity;

    if (steer.Length() > maxForce)
    {
        steer = steer.Normalized() * maxForce;
    }

    applyForce({ steer.x, steer.y });
}

void Vehicle::seekOrArrive(const Vector2& target)
{
    const Vector2f targetF = Vector2f(target.x, target.y);

    float distance = (targetF - position).Length();
    if (distance < 150.0f) 
    {
        arrive(target);
    }
    else {
        seek(target);
    }
}

void Vehicle::boundaries()
{
    Vector2f* desired = nullptr;
    if (position.x < bounds.x)
    {
        desired = new Vector2f(maxSpeed, velocity.y);
    }
    else if (position.x > 1280 - bounds.x)
    {
        desired = new Vector2f(-maxSpeed, velocity.y);
    }

    if (position.y < bounds.y)
    {
        desired = new Vector2f(velocity.x, maxSpeed);
    }
    else if (position.y > 720 - bounds.y)
    {
        desired = new Vector2f(velocity.x, -maxSpeed);
    }

    if (desired)
    {
        *desired = desired->Normalized();
        desired->x = desired->x * maxSpeed;
        desired->y = desired->y * maxSpeed;

        Vector2f steer = *desired - velocity;

        if (steer.Length() > maxForce)
        {
            steer = steer.Normalized() * maxForce;
        }

        applyForce({ steer.x, steer.y });
    }

    delete desired;
}

std::shared_ptr<Collision> Vehicle::getCollision() const
{
    return m_collision;
}

void Vehicle::die()
{
    bIsAlive = false;
}

bool Vehicle::isAlive() const
{
    return bIsAlive;
}

float Vehicle::getAngle() const
{
    return atan2f(velocity.y, velocity.x);
}

float Vehicle::map(float value, float in_min, float in_max, float out_min, float out_max)
{
    value = std::fmax(in_min, std::fmin(value, in_max));
    return out_min + (out_max - out_min) * ((value - in_min) / (in_max - in_min));
}

Vector2f Vehicle::getNormalPoint(Vector2f future, Vector2f start, Vector2f end)
{
    Vector2f ap = future - start;
    Vector2f ab = (end - start).Normalized();

    float dot = ap.x * ab.x + ap.y * ab.y;
    Vector2f projection = ab * dot;

    Vector2f normalPoint = start + projection;

    return normalPoint;
}

float Vehicle::Vector2Distance(const Vector2f& a, const Vector2f& b)
{
    return (b - a).Length();
}
