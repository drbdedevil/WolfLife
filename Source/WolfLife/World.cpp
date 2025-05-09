#include "World.h"

#include "Agents/Dog.h"
#include "Agents/Wolf.h"
#include "Agents/Sheep.h"
#include "raylib.h"
#include "Components/Collision.h"
#include "Components/Eyeshot.h"
#include "Components/Path.h"

#include <algorithm>
#include <iostream>

World::World(int countOfSheep, int countOfDogs) : m_countOfSheep(countOfSheep), m_countOfDogs(countOfDogs)
{
	reset();
}

World::~World()
{

}

void World::reset()
{
	onWolfNoticed = std::make_unique<eventpp::CallbackList<void()>>();
	onWolfDisappeared = std::make_unique<eventpp::CallbackList<void()>>();

	m_wolf.reset(new Wolf(50, 50, 20));

	generateSheepVehicles();
	generateDogVehicles();
	vehiclesAccounting();
}

void World::doForce()
{
	Vector2 mousePos = GetMousePosition();

	m_wolf->arrive(mousePos);
	for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		sheep->execute();
	}
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		dog->execute();
	}
}

void World::update(float DeltaSeconds)
{
	checkVisibility();
	checkCollisions();
	checkAliveVehicle();

	m_wolf->update(DeltaSeconds);
	for (Vehicle* vehicle : m_allVehicles)
	{
		vehicle->flock(m_allVehicles);
		// vehicle->separate(m_allVehicles);
		vehicle->update(DeltaSeconds);
	}
	/*for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		sheep->update(DeltaSeconds);
	}
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		dog->update(DeltaSeconds);
	}*/
}

void World::draw()
{
	ClearBackground({0, 52, 10, 0});

	DrawRectangle(107, 60, 1066, 600, { 30, 102, 30, 255 });
	DrawRectangleRoundedLinesEx({107, 60, 1066, 600}, 0.0, 2, 2.f, BROWN);

	// m_dogPath->draw();

	m_wolf->draw();
	for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		sheep->draw();
	}
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		dog->draw();
	}
}

void World::gameOver()
{
	m_wolf->die();
}

bool World::isGameOver() const
{
	return !m_wolf->isAlive() || m_sheep.size() == 0;
}

std::shared_ptr<Wolf> World::getWolf() const
{
	return m_wolf;
}

int World::getCountOfSheep() const
{
	return m_sheep.size();
}

int World::getWolfHealth() const
{
	return m_wolf->getHealth();
}

void World::generateSheepVehicles()
{
	m_sheep.clear();
	m_sheep.resize(m_countOfSheep);

	size_t column = 0;
	size_t line = 0;
	for (size_t i = 0; i < m_countOfSheep; ++i)
	{
		if (i % 10 == 0)
		{
			line = 0;
			++column;
		}

		m_sheep[i].reset(new Sheep(175 + 40 * column, 175 + 40 * line++));
		m_sheep[i]->setWolf(m_wolf);
		m_sheep[i]->setSheepBehavior(ESheepBehavior::ESB_Pasture);
		onWolfNoticed->append(std::bind(&Sheep::sheepShouldRunningAway, m_sheep[i]));
		onWolfDisappeared->append(std::bind(&Sheep::sheepShouldPasture, m_sheep[i]));
	}
}

void World::generateDogVehicles()
{
	m_dogs.clear();

	const float x = 150.f;
	const float y = 100.f;
	m_dogPath.reset(new Path(20.f/*, Vector2(x, y + 30.f), Vector2(975.f + x, y)*/));
	m_dogPath->clear();

	m_dogPath->addPoint(Vector2(75.f + x, y));
	m_dogPath->addPoint(Vector2(900.f + x, y));
	m_dogPath->addPoint(Vector2(975.f + x, 75.f + y));
	m_dogPath->addPoint(Vector2(975.f + x, 425.f + y));
	m_dogPath->addPoint(Vector2(900.f + x, 500.f + y));
	m_dogPath->addPoint(Vector2(75.f + x, 500.f + y));
	m_dogPath->addPoint(Vector2(x, 425.f + y));
	m_dogPath->addPoint(Vector2(x, 75.f + y));

	m_dogs.resize(m_countOfDogs);
	size_t column = 0;
	size_t line = 0;
	for (size_t i = 0; i < m_countOfDogs; ++i)
	{
		if (i % 2 == 0 && i != 0)
		{
			line = 0;
			++column;
		}

		m_dogs[i].reset(new Dog(x + 975.f * column, y + 500.f * line++));
		m_dogs[i]->setPath(m_dogPath);
		m_dogs[i]->setWolf(m_wolf);
		m_dogs[i]->setDogBehavior(EDogBehavior::EDB_Patrolling);
		onWolfNoticed->append(std::bind(&Dog::dogShouldWolfChase, m_dogs[i]));
		onWolfDisappeared->append(std::bind(&Dog::dogShouldReturn, m_dogs[i]));
	}
}

void World::vehiclesAccounting()
{
	m_allVehicles.clear();

	// m_allVehicles.resize(m_countOfSheep + m_countOfDogs);
	std::transform(
		m_sheep.begin(), m_sheep.end(),
		std::back_inserter(m_allVehicles),
		[](const std::shared_ptr<Sheep>& sheepPtr) {
			return sheepPtr.get();
		});
	std::transform(
		m_dogs.begin(), m_dogs.end(),
		std::back_inserter(m_allVehicles),
		[](const std::shared_ptr<Dog>& dogPtr) {
			return dogPtr.get();
		});
}

bool World::wolfInSafeZone() const
{
	Vector2 wolfPos = { m_wolf->position.x, m_wolf->position.y };
	if ((wolfPos.x < 107 || wolfPos.x > 1173) || (wolfPos.y < 60 || wolfPos.y > 660))
	{
		return true;
	}
	return false;
}

void World::checkVisibility()
{
	Vector2 wolfPos = { m_wolf->position.x, m_wolf->position.y };

	// if wolf in safe zone then it invisible
	if (wolfInSafeZone())
	{
		if (!m_wolf->isVisible())
		{
			return;
		}

		m_wolf->setVisibility(false);
		(*onWolfDisappeared)();
		return;
	}

	if (m_wolf->isVisible())
	{
		return;
	}

	// Check if sheep see wolf
	for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		Vector2 sheepPos = { sheep->position.x, sheep->position.y };

		if (sheep->getEyeshot()->isWolfInEyeshot(wolfPos, m_wolf->getCollision()->getRadius()))
		{
			m_wolf->setVisibility(true);
			(*onWolfNoticed)();
			return;
		}
	}

	// Check if dogs see wolf
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		Vector2 dogPos = { dog->position.x, dog->position.y };

		if (dog->getEyeshot()->isWolfInEyeshot(wolfPos, m_wolf->getCollision()->getRadius()))
		{
			// std::cout << "I SEE YOU!!!" << std::endl;
			m_wolf->setVisibility(true);
			(*onWolfNoticed)();
			return;
		}
	}
}

void World::checkCollisions()
{
	// Check if sheep under wolf
	Vector2 wolfPos = { m_wolf->position.x, m_wolf->position.y };
	for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		Vector2 sheepPos = { sheep->position.x, sheep->position.y };

		if (CheckCollisionCircles(sheepPos, sheep->getCollision()->getRadius(), wolfPos, m_wolf->getCollision()->getRadius()))
		{
			m_wolf->eatSheep(sheep.get());
			m_wolf->setVisibility(true);
			(*onWolfNoticed)();
		}
	}

	// Check if dogs under wolf
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		Vector2 dogPos = { dog->position.x, dog->position.y };

		if (CheckCollisionCircles(dogPos, dog->getCollision()->getRadius(), wolfPos, m_wolf->getCollision()->getRadius()))
		{
			if (!wolfInSafeZone())
			{
				dog->eatWolf(m_wolf.get());
			}
		}
	}
}

void World::checkAliveVehicle()
{
	// Find died sheep
	std::vector<std::shared_ptr<Sheep>> sheepToDie = {};
	for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		if (!sheep->isAlive())
		{
			sheepToDie.push_back(sheep);
		}
	}
	for (std::shared_ptr<Sheep> sheep : sheepToDie)
	{
		auto it = std::find(m_sheep.begin(), m_sheep.end(), sheep);
		if (it != m_sheep.end())
		{
			m_sheep.erase(it);
		}
		auto it2 = std::find(m_allVehicles.begin(), m_allVehicles.end(), sheep.get());
		if (it2 != m_allVehicles.end())
		{
			m_allVehicles.erase(it2);
		}
	}
	// std::cout << m_allVehicles.size() << std::endl;
	
	// Wolf alive?
	if (!m_wolf->isAlive())
	{
		std::cout << "GAME OVER" << std::endl;
	}
}
