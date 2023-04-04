#include "SlashAttack.h"
#include "../../Utilities/Textures.h"

SlashAttack::SlashAttack(int speed, float size, float distance, float range)
	: Attack(speed, size, distance, range, &Textures::ball)
{
}

void SlashAttack::update(const sf::Vector2f& origin)
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
			attackSequence(origin);
		}
	}
	else
	{
		attackSequence(origin);
	}
}

void SlashAttack::attackSequence(const sf::Vector2f& origin)
{
	if (getAttackProgress() > getAttackRange())
	{
		setIsAttacking(false);
		setAttackProgress(0);
		return;
	}

	sf::Vector2f atkSizeOffset = sf::Vector2f(getAttackSize(), getAttackSize()) / 2.f;
	sf::Vector2f atkAreaOffset = sf::Vector2f(getAttackDirection().y, getAttackDirection().x) * (float)getAttackProgress();
	sf::Vector2f atkDistanceOffset = getAttackDirection() * getAttackDistance();
	sf::Vector2f atkRangeOffset = sf::Vector2f(getAttackDirection().y, getAttackDirection().x) * getAttackRange()  / 2.f;

	setAttackCollider(sf::FloatRect
	(
		origin.x - atkSizeOffset.x - atkAreaOffset.x + atkDistanceOffset.x + atkRangeOffset.x,
		origin.y - atkSizeOffset.y - atkAreaOffset.y + atkDistanceOffset.y + atkRangeOffset.y,
		getAttackSize(),
		getAttackSize()
	));
	setAttackSpritePosition(sf::Vector2f(getAttackCollider().left, getAttackCollider().top) + sf::Vector2f(getAttackCollider().width, getAttackCollider().height) / 2.f);

	addAttackProgress(getAttackSpeed());
}
