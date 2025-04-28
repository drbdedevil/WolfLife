#pragma once

#include "raylib.h"
#include <cmath>
#include <memory>

class Collision;

struct Vector2f 
{
    float x, y;

    float Length() const {
        return sqrtf(x * x + y * y);
    }

    Vector2f Normalized() const {
        float len = Length();
        if (len == 0) return { 0, 0 };
        return { x / len, y / len };
    }

    Vector2f operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    Vector2f operator-(const Vector2f& other) const {
        return { x - other.x, y - other.y };
    }

    Vector2f operator+(const Vector2f& other) const {
        return { x + other.x, y + other.y };
    }
};

class Vehicle
{
public:
	Vehicle(int x, int y);
    virtual ~Vehicle() {};

	virtual void update(float DeltaSeconds);
	void applyForce(const Vector2& force);

	virtual void draw();

	// Преследование
	void seek(const Vector2& target);

    // Убегание
    void fleeing(const Vector2& target);

    // Прибытие
    void arrive(const Vector2& target);

    // Преследование или прибытие
    void seekOrArrive(const Vector2& target);

    // Ограничение по границам и убегание
    void fleeingBound(const Vector2& target);

    std::shared_ptr<Collision> getCollision() const;

    void die();
    bool isAlive() const;

    float getAngle() const;
protected:
    std::shared_ptr<Collision> m_collision;

    float map(float value, float in_min, float in_max, float out_min, float out_max);
    Vector2f getNormalPoint(Vector2f future, Vector2f start, Vector2f end);
    float Vector2Distance(const Vector2f& a, const Vector2f& b);
    float randomFloat(float min, float max);

    bool bIsAlive = true;
public:
    Vector2f position;
    Vector2f velocity;
    Vector2f acceleration;

    Vector2 bounds;

	float size;
	float maxSpeed;
	float maxForce;

    bool bShouldBound = false;
};