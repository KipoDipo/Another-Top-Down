#include "SlashAttack.h"

SlashAttack::SlashAttack(int speed, float size, float distance, float range)
	: Attack(speed, size, distance, range)
{
}

void SlashAttack::update(const sf::FloatRect& entityCollider)
{
	using namespace sf;
	sf::Vector2f dir;

	if (!getIsAttacking())
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
			dir = { 0, -1 };
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			dir = { 0, 1 };
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			dir = { -1, 0 };
		else if (Keyboard::isKeyPressed(Keyboard::Right))
			dir = { 1, 0 };

		if (dir != sf::Vector2f(0, 0))
		{
			setIsAttacking(true);
			setAttackDirection(dir);
			attackSequence(entityCollider);
		}
	}
	else
	{
		attackSequence(entityCollider);
	}
}

void SlashAttack::attackSequence(const sf::FloatRect& entityCollider)
{
	if (getAttackProgress() > getAttackRange())
	{
		setIsAttacking(false);
		setAttackProgress(0);
		return;
	}

	sf::Vector2f playerSizeOffset = sf::Vector2f(entityCollider.width, entityCollider.height) / 2.f;
	sf::Vector2f atkSizeOffset = sf::Vector2f(getAttackSize(), getAttackSize()) / 2.f;
	sf::Vector2f atkAreaOffset = sf::Vector2f(getAttackDirection().y, getAttackDirection().x) * (float)getAttackProgress();
	sf::Vector2f atkDistanceOffset = getAttackDirection() * getAttackDistance();
	sf::Vector2f atkRangeOffset = sf::Vector2f(getAttackDirection().y, getAttackDirection().x) * getAttackRange()  / 2.f;

	setAttackCollider(sf::FloatRect
	(
		entityCollider.left + playerSizeOffset.x - atkSizeOffset.x - atkAreaOffset.x + atkDistanceOffset.x + atkRangeOffset.x,
		entityCollider.top + playerSizeOffset.y - atkSizeOffset.y - atkAreaOffset.y + atkDistanceOffset.y + atkRangeOffset.y,
		getAttackSize(),
		getAttackSize()
	));

	addAttackProgress(getAttackSpeed());
}