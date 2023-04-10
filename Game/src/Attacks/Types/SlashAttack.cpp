#include "SlashAttack.h"
#include "../../Utilities/Textures.h"
#include "../../Utilities/Utils.h"

using namespace sf;

SlashAttack::SlashAttack(float speed, float size, float distance, float range)
	: Attack(speed, size, distance, range, Textures::get("ball"))
{
}


void SlashAttack::update(const Vector2f& origin)
{
	if (getIsActive())
	{
		sequence(origin);
	}
	else
	{
		Vector2f dir;

		if (Keyboard::isKeyPressed(Keyboard::Up))
			dir = { 0, -1 };
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			dir = { 0, 1 };
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			dir = { -1, 0 };
		else if (Keyboard::isKeyPressed(Keyboard::Right))
			dir = { 1, 0 };

		if (dir != Vector2f(0, 0))
		{
			setIsActive(true);
			setDirection(dir);
			sequence(origin);
		}
	}
}

void SlashAttack::sequence(const Vector2f& origin)
{
	if (!checkSequence())
		return;

	Vector2f atkSizeOffset = Vector2f(getSize(), getSize()) / 2.f;
	Vector2f atkAreaOffset = Vector2f(getDirection().y, getDirection().x) * getProgress() * getRange();
	Vector2f atkDistanceOffset = getDirection() * getDistance();
	Vector2f atkRangeOffset = Vector2f(getDirection().y, getDirection().x) * getRange() / 2.f;

	setCollider(FloatRect
	(
		origin.x - atkSizeOffset.x - atkAreaOffset.x + atkDistanceOffset.x + atkRangeOffset.x,
		origin.y - atkSizeOffset.y - atkAreaOffset.y + atkDistanceOffset.y + atkRangeOffset.y,
		getSize(),
		getSize()
	));

	setSpritePosition(Vector2f(getCollider().left, getCollider().top) + Vector2f(getCollider().width, getCollider().height) / 2.f);
	addProgress(getSpeed() * Utils::getDeltaTime());
}
