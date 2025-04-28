#pragma once

#include "AIVehicle.h"

class Sheep : public AIVehicle
{
public:
	Sheep(int x, int y);

	virtual void update(float DeltaSeconds) override;
	virtual void draw() override;

	virtual void execute() override;
private:

};