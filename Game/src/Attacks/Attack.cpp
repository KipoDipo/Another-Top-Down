#include "Attack.h"

Attack::Attack(int speed, float size, float distance, float range, const sf::Texture* texture)
	: isAttacking(false), atkProgress(0),
	atkDir(), atkCollider()
{
	setAttackSpeed(speed);
	setAttackSize(size);
	setAttackDistance(distance);
	setAttackRange(range);
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

bool Attack::getIsAttacking() const
{
	return isAttacking;
}

int Attack::getAttackProgress() const
{
	return atkProgress;
}

int Attack::getAttackSpeed() const
{
	return atkSpeed;
}

float Attack::getAttackSize() const
{
	return atkSize;
}

float Attack::getAttackDistance() const
{
	return atkDist;
}

float Attack::getAttackRange() const
{
	return atkRange;
}

sf::Vector2f Attack::getAttackDirection() const
{
	return atkDir;
}

const sf::FloatRect& Attack::getAttackCollider() const
{
	return atkCollider;
}

void Attack::setIsAttacking(bool state)
{
	isAttacking = state;
}

void Attack::setAttackProgress(int progress)
{
	if (progress < 0)
		progress = 0;

	atkProgress = progress;
}

void Attack::addAttackProgress(int plusProgress)
{
	setAttackProgress(getAttackProgress() + plusProgress);
}

void Attack::setAttackSpeed(int speed)
{
	if (speed < 1)
		speed = 1;
	atkSpeed = speed;
}

void Attack::setAttackSize(float size)
{
	if (size < 1)
		size = 1;
	atkSize = size;
}

void Attack::setAttackDistance(float distance)
{
	atkDist = distance;
}

void Attack::setAttackRange(float range)
{
	if (range < 1)
		range = 1;
	atkRange = range;
}

void Attack::setAttackDirection(sf::Vector2f direction)
{
	atkDir = direction;
}

void Attack::setAttackCollider(const sf::FloatRect& collider)
{
	atkCollider = collider;
}

void Attack::setAttackSpritePosition(const sf::Vector2f position)
{
	sprite.setPosition(position);
}