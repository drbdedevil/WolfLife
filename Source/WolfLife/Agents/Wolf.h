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

	void setVisibility(bool Value);
	bool isVisible() const;

	void tear();
private:
	int8_t m_health;
	bool bIsVisible = false;
};