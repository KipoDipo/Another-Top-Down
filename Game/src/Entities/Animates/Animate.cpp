#include "Animate.h"
#include "../Inanimates/Types/Solid.h"

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

void Animate::setDirection(sf::Vector2f direction)
{
	dir = direction;
}

void Animate::setSpeed(float speed)
{
	this->speed = speed;
}

void Animate::resolveCollisions(const Solid* solid, Orientation orientation)
{
	if (collides(*solid))
	{
		if (orientation == Orientation::Horizontal)
		{
			if (dir.x < 0)
				Entity::setPosition(solid->getCollider().left + solid->getCollider().width, collider.top);
			if (dir.x > 0)
				Entity::setPosition(solid->getCollider().left - collider.width, collider.top);
		}
		else if (orientation == Orientation::Vertical)
		{
			if (dir.y < 0)
				Entity::setPosition(collider.left, solid->getCollider().top + solid->getCollider().height);
			if (dir.y > 0)
				Entity::setPosition(collider.left, solid->getCollider().top - collider.height);
		}
	}

}

int Animate::getHealth() const
{
	return health;
}

sf::String Animate::getName() const
{
	return name;
}

sf::Vector2f Animate::getDirection()
{
	return dir;
}

float Animate::getSpeed()
{
	return speed;
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
