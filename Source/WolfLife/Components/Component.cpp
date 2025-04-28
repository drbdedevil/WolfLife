#include "Component.h"

IComponent::IComponent(Vehicle* owner) : m_owner(owner)
{

}

IComponent::~IComponent()
{

}

Vehicle* IComponent::getOwner() const
{
	return m_owner;
}