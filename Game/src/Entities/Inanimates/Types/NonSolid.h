#pragma once
#include "../../Entity.h"

class NonSolid : public Entity
{
public:
	NonSolid();
	NonSolid(sf::Vector2f position);
	NonSolid(sf::Vector2f position, const Animation& sprite);
};
