#pragma once

class Wolf;

class World
{
public:
	void reset();

	void update(float DeltaSeconds);
	void draw();

	bool isGameOver() const;
private:

};