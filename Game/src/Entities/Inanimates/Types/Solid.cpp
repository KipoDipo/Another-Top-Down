#include "Solid.h"

Solid::Solid()
	: Solid(sf::Vector2f(0, 0))
{
}

Solid::Solid(sf::Vector2f position)
	: Solid(position, AnimationCollection::getNone())
{
}

Solid::Solid(sf::Vector2f position, const Animator& animations)
	: Entity(position, animations)
{
}
