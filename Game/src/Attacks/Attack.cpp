#include "Attack.h"

Attack::Attack(float speed, float size, float distance, float range, const sf::Texture* texture)
{
	setIsActive(false);
	setProgress(0);
	setDirection({});
	setCollider({});
	
	setSpeed(speed);
	setSize(size);
	setDistance(distance);
	setRange(range);
	sprite.setTexture(*texture);
	sprite.setOrigin((sf::Vector2f)sprite.getTexture()->getSize() / 2.f);
}

Attack::~Attack()
{
}

void Attack::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
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

float Attack::getSize() const
{
	return size;
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

const sf::FloatRect& Attack::getCollider() const
{
	return collider;
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

void Attack::setSize(float size)
{
	if (size < 1)
		size = 1;
	this->size = size;
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

void Attack::setCollider(const sf::FloatRect& collider)
{
	this->collider = collider;
}

void Attack::setSpritePosition(const sf::Vector2f position)
{
	sprite.setPosition(position);
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
