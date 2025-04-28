#pragma once

#include "raylib.h"
#include <vector>

class Path
{
public:
	Path(float radius/*, const Vector2& start, const Vector2& end*/);

	void draw();

	float getRadius() const;
	const Vector2& getStart() const;
	const Vector2& getEnd() const;

	const std::vector<Vector2>& getPoints() const;

	void addPoint(const Vector2& vector);
private:
	std::vector<Vector2> m_points;

	Vector2 m_start;
	Vector2 m_end;

	float m_radius;
};