#pragma once
#include "../../Entity.h"

class Solid : public Entity
{
public:
	Solid();
	Solid(sf::Vector2f position);
	Solid(sf::Vector2f position, sf::Texture* texture);
};
