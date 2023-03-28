#include "Animate.h"

Animate::Animate()
	: Entity(), health(1)
{
}

Animate::Animate(sf::Vector2f position, sf::Texture* texture)
	: Entity(position, texture), health(1)
{
}

void Animate::addHealth(int toAdd)
{
	setHealth(getHealth() + toAdd);
}

void Animate::subHealth(int toSubtract)
{
	setHealth(getHealth() - toSubtract);
}

void Animate::setHealth(int health)
{
	if (health < 0)
		health = 0;
	this->health = health;
}

void Animate::setName(sf::String name)
{
	this->name = name;
}

int Animate::getHealth() const
{
	return health;
}

sf::String Animate::getName() const
{
	return name;
}

void Animate::kill()
{
	isAlive = false;
	setPosition(-10000, -10000);
}

bool Animate::getIsAlive() const
{
	return isAlive;
}
