#pragma once

class Vehicle;

class IComponent
{
public:
	IComponent(Vehicle* owner);
	virtual ~IComponent();

	virtual void draw() = 0;

	Vehicle* getOwner() const;
protected:
	Vehicle* m_owner;
private:

};