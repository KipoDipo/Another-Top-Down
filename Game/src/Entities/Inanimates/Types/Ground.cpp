#include "Ground.h"
#include "../../../Utilities/Textures.h"

Ground::Ground()
	: Ground(sf::Vector2f(0, 0))
{
}

Ground::Ground(sf::Vector2f position)
	: Ground(position, Textures::get("defaultGround"))
{
}

Ground::Ground(sf::Vector2f position, sf::Texture* texture)
	: Entity(position, texture)
{
}
