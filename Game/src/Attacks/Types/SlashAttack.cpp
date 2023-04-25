#include "../../Utilities/All.h"
#include "SlashAttack.h"

using namespace sf;

SlashAttack::SlashAttack(float speed, float size, float distance, float range, const Animation& animation)
	: Attack(speed, size, distance, range, animation)
{
}


void SlashAttack::update(const Vector2f& origin)
{	
	if (!getIsActive())
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
	addProgress(getSpeed() * DeltaTime::get());
}

SlashAttack* SlashAttack::clone() const
{
	return new SlashAttack(*this);
}
