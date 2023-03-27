#pragma once
#include <SFML/Graphics.hpp>
#include "../Entity.h"

class Player;

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f position);
	Enemy();
private:
};