#pragma once

#include "AIVehicle.h"

class Wolf;

class Dog : public AIVehicle
{
public:
	Dog(int x, int y);

	virtual void update(float DeltaSeconds) override;
	virtual void draw() override;

	void eatWolf(Wolf* wolf);
private:

};