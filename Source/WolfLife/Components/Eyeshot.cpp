#include "Eyeshot.h"
#include <cmath>

#include "../Agents/Vehicle.h"

Eyeshot::Eyeshot(Vehicle* owner, float length, float widthFront, float widthBack) : IComponent(owner)
{
	m_topLeft = { 0, -widthFront / 2 };
	m_topRight = { 0, widthFront / 2 };
	m_bottomLeft = { length, -widthBack / 2 };
	m_bottomRight = { length, widthBack / 2 };
}

void Eyeshot::draw()
{
	std::vector<Vector2> points = 
	{
		m_bottomLeft, m_topLeft, m_bottomRight, m_topRight
	};

	DrawTriangleStrip(points.data(), 4, { 255, 0, 0, 80 });
}

bool Eyeshot::isWolfInEyeshot(const Vector2& circleCenter, float circleRadius)
{
	Vector2 pos = Vector2(m_owner->position.x, m_owner->position.y);
    float angle = m_owner->getAngle();
    std::vector<Vector2> points;
    for (const auto& localPoint : { m_bottomLeft, m_bottomRight, m_topRight, m_topLeft })
    {
        float rotatedX = localPoint.x * cosf(angle) - localPoint.y * sinf(angle);
        float rotatedY = localPoint.x * sinf(angle) + localPoint.y * cosf(angle);
        points.emplace_back(pos.x + rotatedX, pos.y + rotatedY);
    }

	if (isPointInTrapezoid(circleCenter, points)) 
	{
		return true;
	}

	for (int i = 0; i < 4; i++) {
		Vector2 p1 = points[i];
		Vector2 p2 = points[(i + 1) % 4];

		float dist = distancePointToLineSegment(circleCenter, p1, p2);
		if (dist <= circleRadius) {
			return true;
		}
	}

	return false;
}

bool Eyeshot::isPointInTrapezoid(const Vector2& point, const std::vector<Vector2>& trapezoidPoints)
{
	if (trapezoidPoints.size() != 4) return false;

	auto crossProduct = [](Vector2 a, Vector2 b, Vector2 c) {
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
		};

	float d1 = crossProduct(trapezoidPoints[0], trapezoidPoints[1], point);
	float d2 = crossProduct(trapezoidPoints[1], trapezoidPoints[2], point);
	float d3 = crossProduct(trapezoidPoints[2], trapezoidPoints[3], point);
	float d4 = crossProduct(trapezoidPoints[3], trapezoidPoints[0], point);

	return (d1 >= 0 && d2 >= 0 && d3 >= 0 && d4 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0 && d4 <= 0);
}

float Eyeshot::distancePointToLineSegment(const Vector2& point, const Vector2& lineStart, const Vector2& lineEnd)
{
    // Вычисляем вектор направления отрезка
    float lineDirX = lineEnd.x - lineStart.x;
    float lineDirY = lineEnd.y - lineStart.y;

    // Вычисляем длину отрезка
    float lineLength = sqrtf(lineDirX * lineDirX + lineDirY * lineDirY);

    // Нормализуем вектор направления (если отрезок не вырожден)
    float normX = 0, normY = 0;
    if (lineLength > 0.0001f) {
        normX = lineDirX / lineLength;
        normY = lineDirY / lineLength;
    }

    // Вектор от начала отрезка к точке
    float pointToStartX = point.x - lineStart.x;
    float pointToStartY = point.y - lineStart.y;

    // Проекция вектора pointToStart на направление отрезка
    float projection = pointToStartX * normX + pointToStartY * normY;

    // Если проекция вне отрезка - возвращаем расстояние до ближайшей вершины
    if (projection <= 0) {
        float dx = point.x - lineStart.x;
        float dy = point.y - lineStart.y;
        return sqrtf(dx * dx + dy * dy);
    }
    if (projection >= lineLength) {
        float dx = point.x - lineEnd.x;
        float dy = point.y - lineEnd.y;
        return sqrtf(dx * dx + dy * dy);
    }

    // Находим ближайшую точку на отрезке
    float closestX = lineStart.x + normX * projection;
    float closestY = lineStart.y + normY * projection;

    // Возвращаем расстояние от точки до ближайшей точки на отрезке
    float dx = point.x - closestX;
    float dy = point.y - closestY;
    return sqrtf(dx * dx + dy * dy);
}
