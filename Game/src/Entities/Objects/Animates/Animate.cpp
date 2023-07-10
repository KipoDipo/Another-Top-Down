#include "Animate.h"
#include <Utilities/Utils.h>
#include <Entities/Objects/Inanimates/Inanimate.h>
#include <Utilities/ConsoleColors.h>

//#define COLLIDER_DEBUG

using namespace sf;

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

void Animate::setSpeed(float speed)
{
	this->speed = speed;
}

void Animate::setAnimation(AnimateAnimator::State state)
{
	animator.set(state);
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

float Animate::getSpeed() const
{
	return speed;
}

const RandomAnimator& Animate::getDeathParticlesAnimator() const
{
	return deathParticlesAnimator;
}

void Animate::move(sf::Vector2f position, bool collides)
{
	move(position.x, position.y, collides);
}

void Animate::move(float x, float y, bool collides)
{
	bool moveVer = true, moveHor = true;

	if (collides)
	{
		FloatRect testHor, testVer;
		testHor = testVer = Entity::getCollider();

		testHor.left += x;
		testVer.top += y;

		for (size_t i = 0; i < getLevel().getSolids().size(); i++)
		{
			if (getLevel().getSolids()[i]->collides(testHor))
				moveHor = false;
			if (getLevel().getSolids()[i]->collides(testVer))
				moveVer = false;	
		}
	}

	if (moveHor)
		Entity::move(x, 0);
	if (moveVer)
		Entity::move(0, y);

	animator.getSprite().setPosition(Entity::getPosition());
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