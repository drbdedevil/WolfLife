#pragma once

#include "raylib.h"
#include <cmath>

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

	void update(float DeltaSeconds);
	void applyForce(const Vector2& force);

	void draw();

	// Преследование
	void seek(const Vector2& target);

    // Убегание
    void fleeing(const Vector2& target);

    // Прибытие
    void arrive(const Vector2& target);

    // Преследование или прибытие
    void seekOrArrive(const Vector2& target);

    // Ограничение по границам
    void boundaries();
private:


    float map(float value, float in_min, float in_max, float out_min, float out_max);
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