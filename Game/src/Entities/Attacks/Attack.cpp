#include "Attack.h"

Attack::Attack(float speed, float size, float distance, float range, const GenericAnimator& animations)
	: Entity(sf::Vector2f(0,0), sf::Vector2f(size,size)), 
	animator(animations)
{
	setIsActive(false);
	setProgress(0);
	setDirection({});
	
	setSpeed(speed);
	setDistance(distance);
	setRange(range);
	this->animator.get().setOrigin((sf::Vector2f)animator.get().getSize() / 2.f);
}

Attack::~Attack()
{
}

bool Attack::getIsActive() const
{
	return isActive;
}

// returns the progress of the attack from 0.0 to 1.0
float Attack::getProgress() const
{
	return progress;
}

float Attack::getSpeed() const
{
	return speed;
}

float Attack::getDistance() const
{
	return distance;
}

float Attack::getRange() const
{
	return range;
}

sf::Vector2f Attack::getDirection() const
{
	return direction;
}

void Attack::setIsActive(bool state)
{
	isActive = state;
}

void Attack::setProgress(float progress)
{
	if (progress < 0)
		progress = 0;
	
	else if (progress > 1.0001) // to account for floating point errors
	{
		isActive = false;
		progress = 0;
	}

	this->progress = progress;
}

void Attack::addProgress(float plusProgress)
{
	setProgress(progress + plusProgress);
}

void Attack::setSpeed(float speed)
{
	if (speed < 0.f)
		speed = 1.f;
	this->speed = speed;
}

void Attack::setDistance(float distance)
{
	this->distance = distance;
}

void Attack::setRange(float range)
{
	if (range < 1)
		range = 1;
	this->range = range;
}

void Attack::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

void Attack::setPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Attack::setPosition(float x, float y)
{
	Entity::setPosition(x, y);
	animator.get().setPosition(sf::Vector2f(getCollider().left, getCollider().top) + sf::Vector2f(getCollider().width, getCollider().height) / 2.f);
}

void Attack::updateAnimation()
{
	animator.update();
}

void Attack::start(sf::Vector2f direction)
{
	setIsActive(true);
	setDirection(direction);
	setProgress(0);
}

void Attack::stop()
{
	setIsActive(false);
	setProgress(0);
}

void Attack::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animator, states);
}
