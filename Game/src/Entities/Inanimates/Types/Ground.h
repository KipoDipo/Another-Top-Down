#pragma once
#include "../../Entity.h"

class Ground : public Entity
{
public:
	Ground();
	Ground(sf::Vector2f position);
	Ground(sf::Vector2f position, sf::Texture* texture);
};
