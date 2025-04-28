#pragma once

#include <vector>
#include "raylib.h"
#include "Component.h"

class Vehicle;

class Eyeshot : public IComponent
{
public:
	Eyeshot(Vehicle* owner, float length, float widthFront, float widthBack);

    virtual void draw() override;

    bool isWolfInEyeshot(const Vector2& circleCenter, float circleRadius);
    bool isPointInTrapezoid(const Vector2& point, const std::vector<Vector2>& trapezoidPoints);
    float distancePointToLineSegment(const Vector2& point, const Vector2& lineStart, const Vector2& lineEnd);
private:
    Vector2 m_topLeft;
    Vector2 m_topRight;
    Vector2 m_bottomRight;
    Vector2 m_bottomLeft;
};