#include "Solid.h"

Solid::Solid()
	: Solid(sf::Vector2f(0, 0))
{
}

Solid::Solid(sf::Vector2f position)
	: Solid(position, Textures::get("defaultSolid"))
{
}

Solid::Solid(sf::Vector2f position, sf::Texture* texture)
	: Entity(position, texture)
{
}
