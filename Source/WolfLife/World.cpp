#include "World.h"

#include "raylib.h"

void World::reset()
{

}

void World::update(float DeltaSeconds)
{

}

void World::draw()
{
	ClearBackground({0, 52, 10, 0});

	DrawRectangle(107, 60, 1066, 600, BLACK);
	DrawRectangleRoundedLinesEx({107, 60, 1066, 600}, 0.0, 2, 2.f, BROWN);
}

bool World::isGameOver() const
{
	return false;
}
