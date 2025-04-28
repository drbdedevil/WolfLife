#pragma once

#include "Component.h"

class Vehicle;

class Collision : public IComponent
{
public:
	Collision(Vehicle* owner, float radius);

	virtual void draw() override;

	bool checkCollision();

	float getRadius() const;
private:
	float m_radius;
};