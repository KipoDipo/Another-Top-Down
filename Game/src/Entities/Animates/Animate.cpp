#include "Animate.h"
#include "../Inanimates/Types/Solid.h"
#include "../../Utilities/Utils.h"

Animate::Animate()
	: Entity(), health(1), speed(0)
{
}

Animate::Animate(sf::Vector2f position, const Animator& animations, float speed)
	: Entity(position, animations)
{
	setHealth(1);
	setSpeed(speed);
}

void Animate::addHealth(int toAdd)
{
	setHealth(health + toAdd);
}

void Animate::subHealth(int toSubtract)
{
	setHealth(health - toSubtract);
}

void Animate::setHealth(int health)
{
	if (health < 0)
		health = 0;
	this->health = health;
}

void Animate::setName(const std::string& name)
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

void Animate::resolveCollisions(const Entity* entity, Orientation orientation)
{
	if (collides(*entity))
	{
		switch (orientation)
		{
		case Orientation::Horizontal:
			if (dir.x < 0)
				Entity::setPosition(entity->getCollider().left + entity->getCollider().width, getCollider().top);
			else if (dir.x > 0)
				Entity::setPosition(entity->getCollider().left - getCollider().width, getCollider().top);
			break;
		case Orientation::Vertical:
			if (dir.y < 0)
				Entity::setPosition(getCollider().left, entity->getCollider().top + entity->getCollider().height);
			else if (dir.y > 0)
				Entity::setPosition(getCollider().left, entity->getCollider().top - getCollider().height);
			break;
		}
	}

}

void Animate::addCollidable(Entity* entity)
{
	collidablesList.push_back(entity);
}

void Animate::clearCollidables()
{
	collidablesList.clear();
}

int Animate::getHealth() const
{
	return health;
}

std::string Animate::getName() const
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

const std::vector<Entity*>& Animate::getCollidablesList() const
{
	return collidablesList;
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
