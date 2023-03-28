#pragma once
#include "../Animate.h"

class Player;

class Enemy : public Animate
{
public:
	Enemy();
	Enemy(sf::Vector2f position);
private:

	// Inherited via Animate
	virtual void update() override;
	virtual void movement() override;
};