#pragma once

#include "Vehicle.h"

class Sheep;

class Wolf : public Vehicle
{
public:
	Wolf(int x, int y, int8_t health);

	virtual void update(float DeltaSeconds) override;
	virtual void draw() override;

	int8_t getHealth() const;

	void eatSheep(Sheep* sheep);
private:
	int8_t m_health;
};