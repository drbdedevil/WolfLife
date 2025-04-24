#include "AIVehicle.h"

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
