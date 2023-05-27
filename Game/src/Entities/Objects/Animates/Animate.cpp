#include "Animate.h"
#include "../../../Utilities/Utils.h"

Animate::Animate()
	: Animate(sf::Vector2f(0,0), sf::Vector2f(50,50), AnimateAnimator(), 0)
{
}

Animate::Animate(sf::Vector2f position, sf::Vector2f size, const AnimateAnimator& animator, float speed)
	: Entity(position, size), animator(animator)
{
	setHealth(1);
	setSpeed(speed);
	this->animator.get().setPosition(position);
}

void Animate::update()
{
	Entity::update();
	animator.update();
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

void Animate::setAnimation(AnimateAnimator::State state)
{
	animator.setState(state);
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
		animator.get().setPosition(Entity::getPosition());
	}

}

void Animate::addCollidable(std::shared_ptr<Entity> entity)
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

sf::Vector2f Animate::getDirection() const
{
	return dir;
}

float Animate::getSpeed() const
{
	return speed;
}

const std::vector<std::shared_ptr<Entity>>& Animate::getCollidablesList() const
{
	return collidablesList;
}

void Animate::move(sf::Vector2f position)
{
	move(position.x, position.y);
}

void Animate::move(float x, float y)
{
	Entity::move(x, y);
	animator.get().move(x, y);
}

void Animate::kill()
{
	isAlive = false;
	Entity::setPosition(-10000, -10000);
	animator.get().setPosition(Entity::getPosition());
}

bool Animate::getIsAlive() const
{
	return isAlive;
}

void Animate::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isAlive)
		return;

	target.draw(animator, states);

#ifdef COLLIDER_DEBUG
	Entity::draw(target, states);
#endif
}