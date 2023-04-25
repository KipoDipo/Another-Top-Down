#include "Solid.h"
#include "../../../Utilities/Textures.h"

Solid::Solid()
	: Solid(sf::Vector2f(0, 0))
{
}

Solid::Solid(sf::Vector2f position)
	: Solid(position, Animations::getNone())
{
}

Solid::Solid(sf::Vector2f position, const Animation& sprite)
	: Entity(position, sprite)
{
}
