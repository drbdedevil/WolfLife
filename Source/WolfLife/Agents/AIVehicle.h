#pragma once

#include "Vehicle.h"

class Path;
class Eyeshot;

class AIVehicle : public Vehicle
{
public:
	AIVehicle(int x, int y);
	virtual ~AIVehicle();

	virtual void update(float DeltaSeconds) override;
	virtual void draw() override;

	virtual void execute() = 0;

	std::shared_ptr<Eyeshot> getEyeshot() const;
protected:
	std::shared_ptr<Eyeshot> m_eyeshot;
	Vector2 m_startPos;
private:
};