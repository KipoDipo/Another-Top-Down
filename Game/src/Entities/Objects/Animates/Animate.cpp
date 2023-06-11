#include "Animate.h"
#include <Utilities/Utils.h>

//#define COLLIDER_DEBUG

Animate::Animate()
	: Animate(sf::Vector2f(0,0), sf::Vector2f(50,50), AnimateAnimator(), RandomAnimator(), 0, nullptr)
{
}

Animate::Animate(sf::Vector2f position, sf::Vector2f size, const AnimateAnimator& animator, const RandomAnimator& deathParticlesAnimator, float speed, Level* level)
	: Entity(position, size, level),
	animator(animator), deathParticlesAnimator(deathParticlesAnimator)
{
	setMaxHealth(1);
	setHealth(1);
	setSpeed(speed);
	this->animator.getSprite().setPosition(position - (sf::Vector2f)this->animator.getSprite().getTexture()->getSize() / 2.f + size / 2.f);
}

void Animate::update()
{
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

void Animate::setMaxHealth(int health)
{
	if (health < 0)
		maxHealth = 0;
	this->maxHealth = health;
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
	animator.set(state);
}

void Animate::resolveCollisions(const Entity& entity, Orientation orientation)
{
	if (collides(entity))
	{
		sf::Vector2f newPosition;
		switch (orientation)
		{
		case Orientation::Horizontal:
			if (dir.x < 0)
				newPosition = sf::Vector2f(entity.getCollider().left + entity.getCollider().width, Entity::getCollider().top);
			else if (dir.x > 0)
				newPosition = sf::Vector2f(entity.getCollider().left - Entity::getCollider().width, Entity::getCollider().top);
			break;
		case Orientation::Vertical:
			if (dir.y < 0)
				newPosition = sf::Vector2f(Entity::getCollider().left, entity.getCollider().top + entity.getCollider().height);
			else if (dir.y > 0)
				newPosition = sf::Vector2f(Entity::getCollider().left, entity.getCollider().top - Entity::getCollider().height);
			break;
		}
		animator.getSprite().move(newPosition - Entity::getPosition());
		Entity::setPosition(newPosition);
	}

}

int Animate::getHealth() const
{
	return health;
}

int Animate::getMaxHealth() const
{
	return maxHealth;
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

const RandomAnimator& Animate::getDeathParticlesAnimator() const
{
	return deathParticlesAnimator;
}

void Animate::move(sf::Vector2f position)
{
	move(position.x, position.y);
}

void Animate::move(float x, float y)
{
	Entity::move(x, y);
	animator.getSprite().move(x, y);
}

void Animate::kill()
{
	isAlive = false;
	//Entity::setPosition(INT_MIN, INT_MIN);
	//animator.getSprite().setPosition(Entity::getPosition());
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