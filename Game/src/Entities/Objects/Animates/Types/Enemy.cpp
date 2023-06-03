#include <Utilities/All.h>
#include "Enemy.h"
#include "Player.h"
#include <Level.h>
#include <Particles/ParticleGenerator.h>

Enemy::Enemy()
	: Enemy(sf::Vector2f(0, 0), 20, AnimateAnimator(), GenericAnimator(), nullptr)
{
}

Enemy::Enemy(sf::Vector2f position, float speed, const AnimateAnimator& animation, const GenericAnimator& deathParticlesAnimator, Level* level)
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
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i].get(), Orientation::Vertical);

	movement(Orientation::Horizontal);
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i].get(), Orientation::Horizontal);

	Animate::update();
}

void Enemy::kill()
{
	getLevel().addParticles(ParticleGenerator::explosion(getDeathParticlesAnimator(), getCenter(), 300.f, 10, 3.f));
	Animate::kill();
}
