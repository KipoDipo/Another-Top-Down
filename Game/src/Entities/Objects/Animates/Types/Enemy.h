#pragma once
#include "../Animate.h"

class Solid;
enum class Orientation;

class Enemy : public Animate
{
public:
	Enemy();
	Enemy(sf::Vector2f position, float speed, const AnimateAnimator& animation, const RandomAnimator& deathParticlesAnimator, Level* level);

	void setTarget(Entity* target);

	// Inherited via Animate
	virtual void update() override;
	virtual void kill() override;

private:
	// Inherited via Animate
	virtual void movement() override;

	Entity* target;
};