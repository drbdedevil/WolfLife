#include "Collision.h"

#include "raylib.h"

Collision::Collision(Vehicle* owner, float radius) : m_owner(owner), m_radius(radius)
{

}

bool Collision::checkCollision()
{
	return false;
}

Vehicle* Collision::getOwner() const
{
	return m_owner;
}

float Collision::getRadius() const
{
	return m_radius;
}
