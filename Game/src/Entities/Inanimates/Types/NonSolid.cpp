#include "NonSolid.h"
#include "../../../Utilities/Textures.h"

NonSolid::NonSolid()
	: NonSolid(sf::Vector2f(0, 0))
{
}

NonSolid::NonSolid(sf::Vector2f position)
	: NonSolid(position, Animations::getNone())
{
}

NonSolid::NonSolid(sf::Vector2f position, const Animation& sprite)
	: Entity(position, sprite)
{
}
