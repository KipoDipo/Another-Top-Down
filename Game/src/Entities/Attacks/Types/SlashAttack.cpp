#include <Utilities/DeltaTime.h>
#include "SlashAttack.h"

using namespace sf;

SlashAttack::SlashAttack(float speed, float size, float distance, float range, const GenericAnimator& animations)
	: Attack(speed, size, distance, range, animations)
{
}


void SlashAttack::update(const Vector2f& origin)
{	
	if (!getIsActive())
		return;

	updateAnimation();

	Vector2f atkSizeOffset = getSize() / 2.f;
	Vector2f atkAreaOffset = Vector2f(getDirection().y, getDirection().x) * getProgress() * getRange();
	Vector2f atkDistanceOffset = getDirection() * getDistance();
	Vector2f atkRangeOffset = Vector2f(getDirection().y, getDirection().x) * getRange() / 2.f;

	setPosition(
		origin.x - atkSizeOffset.x - atkAreaOffset.x + atkDistanceOffset.x + atkRangeOffset.x,
		origin.y - atkSizeOffset.y - atkAreaOffset.y + atkDistanceOffset.y + atkRangeOffset.y
	);

	addProgress(getSpeed() * DeltaTime::get());
}

std::unique_ptr<Attack> SlashAttack::clone() const
{
	return std::make_unique<SlashAttack>(*this);
}
