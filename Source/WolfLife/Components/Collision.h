#pragma once

class Vehicle;

class Collision
{
public:
	Collision(Vehicle* owner, float radius);

	bool checkCollision();

	Vehicle* getOwner() const;
	float getRadius() const;
private:
	Vehicle* m_owner;
	float m_radius;
};