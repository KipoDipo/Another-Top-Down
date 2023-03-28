#pragma once
#include "../Entity.h"
#include "../../Utilities/Textures.h"

class Solid : public Entity
{
public:
	Solid()
		: Entity(sf::Vector2f(0,0))
	{
	}
	
	Solid(sf::Vector2f position)
		: Entity(position)
	{
		sprite.setTexture(Textures::defaultSolid);
	}
};

