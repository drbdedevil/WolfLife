#include "AIVehicle.h"

#include "../Components/Path.h"
#include "../Components/Eyeshot.h"

AIVehicle::AIVehicle(int x, int y) : Vehicle(x, y)
{

}

AIVehicle::~AIVehicle()
{

}

void AIVehicle::update(float DeltaSeconds)
{
	Vehicle::update(DeltaSeconds);
}

void AIVehicle::draw()
{
	Vehicle::draw();
}

std::shared_ptr<Eyeshot> AIVehicle::getEyeshot() const
{
	return m_eyeshot;
}
