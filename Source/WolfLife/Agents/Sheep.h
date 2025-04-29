#pragma once

#include "AIVehicle.h"
#include <memory>

class Wolf;

enum ESheepBehavior
{
	ESB_Pasture = 0,
	ESB_ReturnToPasture = 1,
	ESB_RunningAway = 2,
};

class Sheep : public AIVehicle
{
public:
	Sheep(int x, int y);

	virtual void update(float DeltaSeconds) override;
	virtual void draw() override;

	virtual void execute() override;

	void setWolf(std::shared_ptr<Wolf>& wolf);
	void setSheepBehavior(ESheepBehavior newBehavior);

	void sheepShouldPasture();
	void sheepShouldReturnToPasture();
	void sheepShouldRunningAway();
private:
	Wolf* m_wolf;
	ESheepBehavior m_sheepBehavior;
};