#include "Dog.h"

#include "raylib.h"
#include "rlgl.h"

#include "Wolf.h"
#include "../Components/Path.h"
#include "../Components/Eyeshot.h"
#include "../Components/Collision.h"

Dog::Dog(int x, int y) : AIVehicle(x, y)
{
    m_startPos = Vector2(x, y);

    m_collision.reset(new Collision(this, 10.f));
    m_eyeshot.reset(new Eyeshot(this, 200.f, 40.f, 250.f));

    velocity = Vector2f{ 50.f, 50.f };

    maxSpeed = 1.2f;
    maxForce = 0.2f;
}

Dog::~Dog()
{

}

void Dog::update(float DeltaSeconds)
{
    AIVehicle::update(DeltaSeconds);
}

void Dog::draw()
{
    // m_path->draw();

    float angle = atan2f(velocity.y, velocity.x);

    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    m_eyeshot->draw();
    // m_collision->draw();

    float width = size * 2.5f;
    float height = size * 2.5f;
    DrawRectangle(-width / 2, -height / 2, width, height, RED);

    rlPopMatrix();
}

void Dog::execute()
{
    if (m_dogBehavior == EDB_Patrolling)
    {
        followCurve(m_path.lock());
    }
    else if (m_dogBehavior == EDB_ReturnToPatrol)
    {
        arrive({ m_startPos.x, m_startPos.y });

        if (CheckCollisionPointCircle({ position.x, position.y }, m_startPos, 20.f))
        {
            dogShouldPatrol();
        }
    }
    else if (m_dogBehavior == EDB_WolfChase)
    {
        seek({ m_wolf->position.x, m_wolf->position.y });
    }
}

void Dog::eatWolf(Wolf* wolf)
{
    wolf->tear();
}

void Dog::follow(const std::shared_ptr<Path>& path)
{
    Vector2f future = velocity.Normalized() * maxSpeed;
    future = position + future;

    Vector2f start = Vector2f{ path->getStart().x, path->getStart().y };
    Vector2f end = Vector2f{ path->getEnd().x, path->getEnd().y };

    Vector2f normalPoint = getNormalPoint(future, start, end);

    Vector2f pathDir = (end - start).Normalized() * 100.f;
    Vector2f target = normalPoint + pathDir;

    float distance = Vector2Distance(normalPoint, future);
    if (distance > path->getRadius())
    {
        seek(Vector2(target.x, target.y));
    }
}

void Dog::followCurve(const std::shared_ptr<Path>& path)
{
    Vector2f future = velocity;
    future = future.Normalized() * maxSpeed;
    future = position + future;

    Vector2f target = Vector2f();
    Vector2f normal = Vector2f();
    float worldRecord = std::numeric_limits<float>::infinity();

    const auto& points = path->getPoints();
    size_t numPoints = points.size();
    for (size_t i = 0; i < numPoints; ++i)
    {
        Vector2f a = Vector2f(points[i].x, points[i].y);
        Vector2f b = Vector2f(points[(i + 1) % numPoints].x, points[(i + 1) % numPoints].y);

        Vector2f normalPoint = getNormalPoint(future, a, b);

        if (normalPoint.x < std::min(a.x, b.x) || normalPoint.x > std::max(a.x, b.x) ||
            normalPoint.y < std::min(a.y, b.y) || normalPoint.y > std::max(a.y, b.y))
        {
            normalPoint = b;
        }

        float distance = (future - normalPoint).Length();

        if (distance < worldRecord)
        {
            worldRecord = distance;
            normal = normalPoint;
            target = normalPoint;

            Vector2f dir = b - a;
            dir = dir.Normalized() * 100.0f;
            target = target + dir;
        }
    }

    if (worldRecord > path->getRadius())
    {
        seek(Vector2(target.x, target.y));
    }
}

bool Dog::isVisible() const
{
    return bIsVisible;
}

void Dog::setVisibility(bool Value)
{
    bIsVisible = Value;
}

void Dog::setPath(std::shared_ptr<Path>& path)
{
    m_path = path;
}

void Dog::setWolf(std::shared_ptr<Wolf>& wolf)
{
    m_wolf = wolf.get();
}

void Dog::setDogBehavior(EDogBehavior newBehavior)
{
    m_dogBehavior = newBehavior;
}

void Dog::dogShouldPatrol()
{
    m_dogBehavior = EDB_Patrolling;

    maxSpeed = 1.2f;
    maxForce = 0.2f;
}

void Dog::dogShouldReturn()
{
    m_dogBehavior = EDB_ReturnToPatrol;

    maxSpeed = 5.2f;
    maxForce = 0.2f;
}

void Dog::dogShouldWolfChase()
{
    m_dogBehavior = EDB_WolfChase;

    maxSpeed = 8.8f;
    maxForce = 0.5f;
}
