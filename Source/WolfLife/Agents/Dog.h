#pragma once

#include "AIVehicle.h"
#include <memory>

class Wolf;
class Path;

enum EDogBehavior
{
	EDB_Patrolling = 0,
	EDB_ReturnToPatrol = 1,
	EDB_WolfChase = 2
};

class Dog : public AIVehicle
{
public:
	Dog(int x, int y);
	~Dog();

	virtual void update(float DeltaSeconds) override;
	virtual void draw() override;

	virtual void execute() override;

	void eatWolf(Wolf* wolf);

	// Следование по пути
	void follow(const std::shared_ptr<Path>& path);
	void followCurve(const std::shared_ptr<Path>& path);

	bool isVisible() const;
	void setVisibility(bool Value);

	void setPath(std::shared_ptr<Path>& path);
	void setWolf(std::shared_ptr<Wolf>& wolf);
	void setDogBehavior(EDogBehavior newBehavior);

	void dogShouldPatrol();
	void dogShouldReturn();
	void dogShouldWolfChase();

	virtual void updateTextureFrame(float DeltaSeconds) override;
private:
	std::weak_ptr<Path> m_path;
	Wolf* m_wolf;
	EDogBehavior m_dogBehavior;

	bool bIsVisible = true;
};