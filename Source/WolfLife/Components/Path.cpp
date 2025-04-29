#include "Path.h"

Path::Path(float radius/*, const Vector2& start, const Vector2& end*/) : m_radius(radius)/*, m_start(start), m_end(end)*/
{
	m_points = std::vector<Vector2>();
}

void Path::draw()
{
	// DrawLineEx(m_start, m_end, m_radius, { 96, 96, 96, 100 });
	// DrawLineEx(m_start, m_end, 2.f, WHITE);

	Vector2 firstPoint = Vector2();
	Vector2 lastPoint = Vector2();
	for (size_t i = 0; i < m_points.size(); ++i)
	{
		if (i == 0)
		{
			firstPoint = m_points[i];
			lastPoint = m_points[i];
			continue;
		}

		DrawLineEx(lastPoint, m_points[i], m_radius, { 96, 96, 96, 100 });
		DrawLineEx(lastPoint, m_points[i], 2.f, WHITE);

		lastPoint = m_points[i];
	}
	DrawLineEx(lastPoint, firstPoint, m_radius, { 96, 96, 96, 100 });
	DrawLineEx(lastPoint, firstPoint, 2.f, WHITE);
}

float Path::getRadius() const
{
	return m_radius;
}

const Vector2& Path::getStart() const
{
	return m_start;
}

const Vector2& Path::getEnd() const
{
	return m_end;
}

const std::vector<Vector2>& Path::getPoints() const
{
	return m_points;
}

void Path::addPoint(const Vector2& vector)
{
	m_points.push_back(vector);
}

void Path::clear()
{
	m_points.clear();
}
