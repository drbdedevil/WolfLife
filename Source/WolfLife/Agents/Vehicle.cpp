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

    // ������ ����������� �������
    // BeginMode2D({ 0 }); // ������� ����� ��� ������, �� ����� ������������ ��� push/pop ������

    // ��������� �������������: ������� � �������
    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    // ������ �����������
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

void Vehicle::fleeingBound(const Vector2& target)
{
    fleeing(target);
    
    const float borderThreshold = 20.f; // ��������� ������ � ������� �������� �����������
    const float worldLeft = 107.f;
    const float worldRight = 1173.f;
    const float worldTop = 60.f;
    const float worldBottom = 660.f;

    Vector2f borderSteer(0.f, 0.f);

    if (position.x < worldLeft + borderThreshold)
    {
        borderSteer.x += randomFloat(500.f, 1000.0f); // ������� �������
        borderSteer.y += randomFloat(-500.f, 500.0f);
    }
    else if (position.x > worldRight - borderThreshold)
    {
        borderSteer.x += randomFloat(-1000.0f, -500.f); // ������� ������
        borderSteer.y += randomFloat(-500.f, 500.0f);
    }

    if (position.y < worldTop + borderThreshold)
    {
        borderSteer.y += randomFloat(500.f, 1000.0f); // ������� ����
        borderSteer.x += randomFloat(-500.0f, 500.f);
    }
    else if (position.y > worldBottom - borderThreshold)
    {
        borderSteer.y += randomFloat(-1000.0f, -500.f); // ������� �����
        borderSteer.x += randomFloat(-500.0f, 500.f);
    }

    if (borderSteer.Length() > 0.0f)
    {
        borderSteer = borderSteer.Normalized() * 10.f;
        applyForce(Vector2(borderSteer.x, borderSteer.y));
    }
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

float Vehicle::randomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}
