#pragma once
#include <SFML/Graphics.hpp>
#include "../Animate.h"

class Player;

class Enemy : public Animate
{
public:
	Enemy(sf::Vector2f position);
	Enemy();
private:

	// Inherited via Animate
	virtual void update() override;
	virtual void movement() override;
};