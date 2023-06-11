#include "Enemy.h"
#include "Player.h"
#include <Utilities/All.h>
#include <Level.h>
#include <Particles/ParticleGenerator.h>
#include <Entities/Objects/Inanimates/Inanimate.h>

Enemy::Enemy()
	: Enemy(sf::Vector2f(0, 0), 20, AnimateAnimator(), RandomAnimator(), nullptr)
{
}

Enemy::Enemy(sf::Vector2f position, float speed, const AnimateAnimator& animation, const RandomAnimator& deathParticlesAnimator, Level* level)
	: Animate(position, sf::Vector2f(50,50), animation, deathParticlesAnimator, speed, level), 
	target(nullptr)
{
}

void Enemy::setTarget(Entity* target)
{
	this->target = target;
}

void Enemy::movement(Orientation orientation)
{
	setDirection({ 0,0 });
	sf::Vector2f direction = Utils::normalized(target->getCenter() - getCenter());

	switch (orientation)
	{
	case Orientation::Horizontal:
		setDirection({ direction.x, 0 });
		break;
	case Orientation::Vertical:
		setDirection({ 0, direction.y });
		break;
	}
	move(getDirection() * getSpeed() * DeltaTime::get());
}

void Enemy::update()
{
	if (!getIsAlive())
		return;

	if (!target)
		return;

	movement(Orientation::Vertical);
	for (size_t i = 0; i < getLevel().getSolids().size(); i++)
		resolveCollisions(*getLevel().getSolids()[i], Orientation::Vertical);

	movement(Orientation::Horizontal);
	for (size_t i = 0; i < getLevel().getSolids().size(); i++)
		resolveCollisions(*getLevel().getSolids()[i], Orientation::Horizontal);

	Animate::update();
}

void Enemy::kill()
{
	getLevel().addParticles(ParticleGenerator::explosion(getDeathParticlesAnimator(), getCenter(), 300.f, 10, 3.f));
	Animate::kill();
}
