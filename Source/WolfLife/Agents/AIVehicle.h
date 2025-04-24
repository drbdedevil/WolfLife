#pragma once

#include "Vehicle.h"

class AIVehicle : public Vehicle
{
public:
	AIVehicle(int x, int y);
	virtual ~AIVehicle();

	virtual void update(float DeltaSeconds) override;
	virtual void draw() override;
private:

};