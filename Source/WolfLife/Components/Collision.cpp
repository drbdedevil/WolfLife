#include "Collision.h"

#include "raylib.h"

Collision::Collision(Vehicle* owner, float radius) : IComponent(owner), m_radius(radius)
{

}

void Collision::draw()
{
	DrawCircle(0, 0, m_radius, { 0, 0, 255, 80 });
}

bool Collision::checkCollision()
{
	return false;
}

float Collision::getRadius() const
{
	return m_radius;
}