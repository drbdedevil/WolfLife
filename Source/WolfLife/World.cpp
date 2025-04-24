#include "World.h"

#include "Agents/Dog.h"
#include "Agents/Wolf.h"
#include "Agents/Sheep.h"
#include "raylib.h"
#include "Components/Collision.h"

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
	m_wolf.reset(new Wolf(50, 50, 3));

	m_sheep.resize(m_countOfSheep);
	for (size_t i = 0; i < m_countOfSheep; ++i)
	{
		m_sheep[i].reset(new Sheep(250, 250 + 10 * i));
	}
	m_dogs.resize(m_countOfDogs);
	for (size_t i = 0; i < m_countOfDogs; ++i)
	{
		m_dogs[i].reset(new Dog(150, 150 + 10 * i));
	}
}

void World::doForce()
{
	Vector2 mousePos = GetMousePosition();

	m_wolf->arrive(mousePos);
	for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		sheep->fleeing({ m_wolf->position.x, m_wolf->position.y });
	}
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		dog->seek({ m_wolf->position.x, m_wolf->position.y });
	}
}

void World::update(float DeltaSeconds)
{
	checkCollisions();
	checkAliveVehicle();

	m_wolf->update(DeltaSeconds);
	for (std::shared_ptr<Sheep> sheep : m_sheep)
	{
		sheep->update(DeltaSeconds);
	}
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		dog->update(DeltaSeconds);
	}
}

void World::draw()
{
	ClearBackground({0, 52, 10, 0});

	DrawRectangle(107, 60, 1066, 600, BLACK);
	DrawRectangleRoundedLinesEx({107, 60, 1066, 600}, 0.0, 2, 2.f, BROWN);

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

bool World::isGameOver() const
{
	return m_wolf->getHealth() == 0 || m_countOfSheep == 0;
}

std::shared_ptr<Wolf> World::getWolf() const
{
	return m_wolf;
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
		}
	}

	// Check if dogs under wolf
	for (std::shared_ptr<Dog> dog : m_dogs)
	{
		Vector2 dogPos = { dog->position.x, dog->position.y };

		if (CheckCollisionCircles(dogPos, dog->getCollision()->getRadius(), wolfPos, m_wolf->getCollision()->getRadius()))
		{
			dog->eatWolf(m_wolf.get());
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
	}

	// Wolf alive?
	if (!m_wolf->isAlive())
	{
		std::cout << "GAME OVER" << std::endl;
	}
}
