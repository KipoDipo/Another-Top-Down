#include "NonSolid.h"

NonSolid::NonSolid()
	: NonSolid(sf::Vector2f(0, 0))
{
}

NonSolid::NonSolid(sf::Vector2f position)
	: NonSolid(position, AnimationCollection::getNone())
{
}

NonSolid::NonSolid(sf::Vector2f position, const Animator& animations)
	: Entity(position, animations)
{
}
