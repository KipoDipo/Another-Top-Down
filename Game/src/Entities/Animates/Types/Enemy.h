#pragma once
#include "../Animate.h"

class Solid;
enum class Orientation;

class Enemy : public Animate
{
public:
	Enemy();
	Enemy(sf::Vector2f position, float speed);
	Enemy(sf::Vector2f position, const AnimateAnimation& animation, float speed);

	void setTarget(Entity* target);

	// Inherited via Animate
	virtual void update() override;

private:
	// Inherited via Animate
	virtual void movement(Orientation orientation) override;

	Entity* target;
};