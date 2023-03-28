#include "Animate.h"

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

int Animate::getHealth() const
{
	return 0;
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
