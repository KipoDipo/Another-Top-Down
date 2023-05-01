#include "../../../Utilities/All.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
	: Enemy(sf::Vector2f(0, 0), 20)
{
}

Enemy::Enemy(sf::Vector2f position, float speed)
	: Animate(position, sf::Vector2f(50,50), AnimateAnimation(), speed), target(nullptr)
{
}

Enemy::Enemy(sf::Vector2f position, const AnimateAnimation& animation, float speed)
	: Animate(position, sf::Vector2f(50,50), animation, speed), target(nullptr)
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

	Entity::update();
	
	if (!target)
		return;
	movement(Orientation::Vertical);
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i], Orientation::Vertical);

	movement(Orientation::Horizontal);
	for (size_t i = 0; i < getCollidablesList().size(); i++)
		resolveCollisions(getCollidablesList()[i], Orientation::Horizontal);
}
