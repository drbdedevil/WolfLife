#pragma once

#include <memory>
#include <vector>
#include "eventpp/callbacklist.h"

class Dog;
class Wolf;
class Path;
class Sheep;

class World
{
public:
	World(int countOfSheep, int countOfDogs);
	~World();

	void reset();

	void doForce();
	void update(float DeltaSeconds);
	void draw();

	bool isGameOver() const;

	std::shared_ptr<Wolf> getWolf() const;
private:
	eventpp::CallbackList<void()> onWolfNoticed;
	eventpp::CallbackList<void()> onWolfDisappeared;

	bool wolfInSafeZone() const;

	void checkVisibility();
	void checkCollisions();
	void checkAliveVehicle();

	int m_countOfDogs;
	int m_countOfSheep;

	std::shared_ptr<Wolf> m_wolf;
	std::vector<std::shared_ptr<Sheep>> m_sheep;
	std::vector<std::shared_ptr<Dog>> m_dogs;

	std::shared_ptr<Path> m_dogPath;
};